#include "industrial_control.h"
#include "ui_industrial_control.h"
#include "data_plot.h"
#include <qapplication.h>
#include <qmessagebox.h>
#include <QDoubleSpinBox>
#include <QFile>
#include <qpalette.h>
#include <qdebug.h>
#include <qspinbox.h>
#include <qpainter.h>
#include <qpen.h>
#include <qbrush.h>
#include <qwt_counter.h>
#include <qlayout.h>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <stdlib.h>
#include <QTime>
#include <QTimer>
#include <QFileDialog>
#include <QDesktopServices>
#include <math.h>

#include <QTextCodec>
#include <iostream>

using namespace std;
#undef  OVEN_EXCHANGE_DEBUG

#define UINT32_SWAP(x) (((x<<24)&0xff000000 ) | ((x<<8)&0x00ff0000) | ((x >>8)&0x0000ff00) | ((x>>24)&0x000000ff))

#define MAX_ASCII_FRAME_SIZE 45 /* максимальная длина ASCII-пакета включая маркеры и символ '\0'  */
#define MAX_FRAME_SIZE 21 /* максимальная длина пакета согласно протоколу ОВЕН */

struct rs485_packet {
	unsigned short address;
	unsigned short addrLen;
	int request;
	unsigned int hash;
	int dataSize;
	unsigned char data[15];
	unsigned short crc;
	int crc_ok;
};

static QString _ERROR_TEXT=QString::fromLocal8Bit("Ошибка:");
static QString _EXIT_TEXT=QString::fromLocal8Bit("Одобрение");
const char *_PLC_EXCHANGE_TXT= "опрос_TPM101>";
static QPalette pal_0;                                         //палитра
static unsigned char tx_buf[TXBUF_SIZE];
static DataPlot *plot, *plot_screen;
//static QRect main_win_geometry, group_0_geometry, group_1_geometry, group_2_geometry, group_3_geometry, group_4_geometry, group_5_geometry, group_6_geometry;
static QRect group_5_geometry, main_win_geometry;

QTextStream outfile;
QTime operator - ( const QTime & t1, const QTime & t2 )
{
        int diff = t2.msecsTo(t1);
        return QTime(diff / HOUR_MS,
                    (diff % HOUR_MS)/ MIN_MS,
                    (diff % MIN_MS) / SEC_MS,
                     diff % SEC_MS);
}

/*=====логирование адресов============================================================================================*/
void industrial_control::log_add_str( QString s )
{qDebug() << s.toLocal8Bit();
 return;
}
/*=====сброс порта====================================================================================================*/
void industrial_control::rs232_release(void)
{char str[256];
 unsigned int err_code;
 if((rs232 != NULL) &&  (rs232 != INVALID_HANDLE_VALUE)) //если есть указатель-адрес порта
    if (!CloseHandle(rs232))                             //порт не закрыт
        {err_code= GetLastError();  
         sprintf(str,"Kernel Fault:Unable close port handle. Сведения:( %x)",  err_code); 
         QMessageBox::critical( 0, _ERROR_TEXT, QString::fromLocal8Bit(str), _EXIT_TEXT );
        }
 rs232 = NULL;
 return;
}
/*=====инициализация порта============================================================================================*/
int industrial_control::rs232_init(QString port_name)
{
 unsigned int err_code;
 char str[256];
 COMMTIMEOUTS CommTimeouts; // объявление переменной структуры, тип: LPCOMMTIMEOUTS для прерывания из WINAPI
 DCB PortDCB;               // объявление переменной структуры, тип: LPDCB для обмена пакетами из WINAPI

 rs232_release();           // сброс указателя-адреса порта
#ifdef __WINDOWS__
 // создаем указатель порта с атрибутами (имя порта, режим:чтение/запись,открыть)
 rs232 = CreateFile((TCHAR*)port_name.utf16(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
 // если порт не получил адрес то ошибка
  if ( rs232 == INVALID_HANDLE_VALUE )
    {err_code= GetLastError();  
     sprintf(str,"Открытие порта com_%d неуспешно. Сведения:( %x)", ui->rs232_ch->value(), err_code);
     QMessageBox::critical( 0, _ERROR_TEXT, QString::fromLocal8Bit(str), _EXIT_TEXT );
     return 0;
    }
 // заполняем структуру DCB тип: LPDCB для обмена пакетами из WINAPI
  PortDCB.DCBlength = sizeof (DCB);     // размер структуры(DCB)
  GetCommState (rs232, &PortDCB);
  PortDCB.BaudRate = 115200;            // Частота обмена
  PortDCB.fBinary = FALSE;              // Binary mode, no EOF check
  PortDCB.fParity = FALSE;              // Enable parity checking
  PortDCB.fOutxCtsFlow = FALSE;         // No CTS output flow control
  PortDCB.fOutxDsrFlow = FALSE;         // No DSR output flow control
  PortDCB.fDtrControl = DTR_CONTROL_DISABLE;// DTR flow control type
  PortDCB.fDsrSensitivity = FALSE;      // DSR sensitivity
  PortDCB.fTXContinueOnXoff = FALSE;    // XOFF continues Tx
  PortDCB.fOutX = FALSE;                // No XON/XOFF out flow control
  PortDCB.fInX = FALSE;                 // No XON/XOFF in flow control
  PortDCB.fErrorChar = FALSE;           // Disable error replacement
  PortDCB.fNull = FALSE;                // Disable null stripping
  PortDCB.fRtsControl = RTS_CONTROL_TOGGLE;// RTS flow control
  PortDCB.fAbortOnError = FALSE;        // Do not abort read/write on error
  PortDCB.XonLim=4;          			// Transmit X-ON threshold
  PortDCB.XoffLim=16;         			// Transmit X-OFF threshold
  PortDCB.ByteSize = 8;                 // Number of bits/byte, 4-8
  PortDCB.Parity = NOPARITY;            // 0-4=no,odd,even,mark,space
  PortDCB.StopBits = ONESTOPBIT;        // 0,1,2 = 1, 1.5, 2
  PortDCB.XonChar=0x11;                 // Tx and Rx X-ON character
  PortDCB.XoffChar=0x13;                // Tx and Rx X-OFF character

  if (!SetCommState (rs232, &PortDCB))  // устанавливаем параметры порта и проверяем на ошибку
    {err_code= GetLastError();
     sprintf(str,"ошибка (Не устанавливается DCB) %x", err_code);
     QMessageBox::critical( 0, _ERROR_TEXT, QString::fromLocal8Bit(str), _EXIT_TEXT );
     rs232_release(); // сброс указателя на порт
     return 0;
    }

  GetCommTimeouts (rs232, &CommTimeouts);
  CommTimeouts.ReadIntervalTimeout = 1000;
  CommTimeouts.ReadTotalTimeoutMultiplier = 0;
  CommTimeouts.ReadTotalTimeoutConstant = 1;
  CommTimeouts.WriteTotalTimeoutMultiplier = 0;
  CommTimeouts.WriteTotalTimeoutConstant = 1000;

  if (!SetCommTimeouts (rs232, &CommTimeouts))
    {err_code= GetLastError();
     sprintf(str,"ошибка (Не устанавливается DCB) Сведения:( %x)", err_code);
     QMessageBox::critical( 0, _ERROR_TEXT, QString::fromLocal8Bit(str), _EXIT_TEXT );
     rs232_release();
     return 0;
    }

  EscapeCommFunction (rs232, SETDTR);
  EscapeCommFunction (rs232, SETRTS);
#endif
  return 1;
}
/*=====посылка пакета=================================================================================================*/
int industrial_control::rs232_tx(unsigned char *tx_buf, unsigned int tx_len)
{unsigned long v;
 unsigned long err;
 COMSTAT comStat;
#ifdef OVEN_EXCHANGE_DEBUG
 {char s0[512], s1[16];
  unsigned int j;
  tx_buf[tx_len]= 0;
 // sprintf(s0, "tx_%02x> [%s]: [ ", schedule_tm, tx_buf);
sprintf(s0, "tx_%02x>[", schedule_tm); 
  for(j=0; j < tx_len; j++)
    {sprintf(s1, "%02x ", tx_buf[j]);
	 strcat(s0, s1);
	}
  strcat(s0, "]");
  qDebug() << s0;
 }
#endif
 WriteFile (rs232, tx_buf, tx_len, &v, NULL);
 if (v != tx_len)
    {char str[256];
     sprintf(str, "- передача пакета %s в TPM101 неуспешна ", tx_buf);
     if (!ClearCommError(rs232, &err, &comStat))
        {log_add_str(QString::fromLocal8Bit(str)); rs232_tx_err++;return 0;}
     if(err & CE_DNS) strcat(str," fDNS-error; "); 
     if(err & CE_IOE) strcat(str," fIOES-error; ");
     if(err & CE_OOP) strcat(str," fOOP-error; ");
     if(err & CE_PTO) strcat(str," fPTO-error; ");
     if(err & CE_MODE) strcat(str," fMODE-error; ");
     if(err & CE_BREAK) strcat(str," fBREAK-error; ");
     if(err & CE_FRAME) strcat(str," fFRAME-error; ");
     if(err & CE_RXOVER) strcat(str," fRXOVER-error; ");
     if(err & CE_TXFULL) strcat(str," fTXFULL-error; ");
     if(err & CE_OVERRUN) strcat(str," fOVERRUN-error; ");
     if(err & CE_RXPARITY) strcat(str," fRXPARITY-error; ");
     log_add_str(QString::fromLocal8Bit(str));
     rs232_tx_err++;
     return 0;
    }
 rs232_tx_ok++;
 return 1;    
}
/*=====получение ответа===============================================================================================*/
int industrial_control::rs232_rx(unsigned char *rx_buf, unsigned int nbytes)
{unsigned long n;
 unsigned long err;
 COMSTAT comStat;
 ClearCommError(rs232, &err, &comStat);
 if(err)
    {return 0;}
 ReadFile (rs232, rx_buf, nbytes, &n, 0);  /* чтение данных полученых с ком порта */
 if(!n) 
    {char str[256];
     sprintf(str, "%s schedule=0x%x: нет ответа от контроллера.", _PLC_EXCHANGE_TXT, schedule_tm);
     log_add_str(QString::fromLocal8Bit(str));
     memset(tx_buf, 0, TXBUF_SIZE);
     return 0;
    }
 if(n > 80)
    n = 80;
#ifdef OVEN_EXCHANGE_DEBUG
 {char s0[512], s1[16];
  unsigned int j;
  rx_buf[n]= 0;
//  sprintf(s0, "rx_%02x> [%s] : [ ", schedule_tm, rx_buf);
sprintf(s0, "rx_%02x>[", schedule_tm); 
  for(j=0; j < n; j++)
    {sprintf(s1, "%02x ", rx_buf[j]);
	 strcat(s0, s1);
	}
 strcat(s0, "]");	
 qDebug() << s0;
 }
#endif
 return n;
}
/*=====СRC============================================================================================================*/
unsigned short industrial_control::owenCRC16(unsigned char* packet, int length) /* расчет контрольной суммы */
{int i, j;
 unsigned short crc;
 if(packet == NULL)
 	return 0;
 crc = 0;
 for (i = 0; i < length; ++i)
	{unsigned char b = packet[i];
	 for (j = 0; j < 8; ++j, b <<= 1)
		{if ((b ^ (crc >> 8)) & 0x80)
			{crc <<= 1;
			 crc ^= 0x8F57;
			}
		 else
			crc <<= 1;
		}
	}
 return crc;
}
/*====================================================================================================================*/
/* Быстрый алгоритм расчета контрольной суммы с использованием таблицы */
/* таблица */
unsigned short fastCRC16Table[256];
/* инициализация таблицы*/
void industrial_control::initFastCRC16Table(void)
{unsigned short i, j;
 unsigned short crc;
 for (i = 0; i < 256; ++i)
	{unsigned short b = i;
	 crc = 0;
	 for (j = 0; j < 8; ++j, b <<= 1)
		{if ((b ^ (crc >> 8)) & 0x80)
			{crc <<= 1;
			 crc ^= 0x8F57;
			}
		 else
			crc <<= 1;
		}
	 fastCRC16Table[i] = crc;
	}
}
/* быстрый расчет контрольной суммы */
unsigned short industrial_control::owenFastCRC16(unsigned char* packet, int length)
{int i;
 unsigned short crc;
 if(packet == NULL)
 	return 0;
 crc = 0;
 for (i = 0; i < length; ++i)
    {crc = (crc << 8) ^ fastCRC16Table[(crc >> 8) ^ packet[i]];}
 return crc;
}
/*====================================================================================================================*/
int industrial_control::packFrameToAscii(unsigned char* frame, int frame_size, unsigned char* frameAscii, int max_ascii_frame_size)
{int i, j;
 char str[256];
 if((frameAscii == NULL) || (frame== NULL))
    {sprintf(str,"%s> [%d] tm=0x%x error",  __FUNCTION__, __LINE__, schedule_tm);
	 log_add_str(QString::fromLocal8Bit( str));		
	 return 0;
	}
 if(max_ascii_frame_size < (frame_size*2+2+1))
    {sprintf(str,"%s> [%d] tm=0x%x error (ascii_frame_size= %d)",  __FUNCTION__, __LINE__,  schedule_tm, frame_size*2+2+1);
	 log_add_str(QString::fromLocal8Bit( str));			
	 return 0;
	}
 frameAscii[0] = '#';
 for (i = 0, j = 1; i < frame_size; ++i, j += 2)
	{frameAscii[j] = 'G' + ((frame[i] >> 4) & 0x0f);
	 frameAscii[j + 1] = 'G' + (frame[i] & 0x0f);
	}
 frameAscii[frame_size*2+1] = 0x0d;
 frameAscii[frame_size*2+2] = 0x00;
 return 1;
}
/*====================================================================================================================*/
int industrial_control::unpackAsciiFrame(unsigned char* frameAscii, int frameAsciiSize, unsigned char* frame, int frame_size)
{int i, j;
 char str[256];
 if((frameAscii == NULL) || (frame== NULL))
	return 0;
 if(frameAscii[0] != '#' || frameAscii[frameAsciiSize - 1] != 0xd)
    {sprintf(str,"%s> [%d] tm=0x%x error rxbuf[%d]= 0x%02x",  __FUNCTION__, __LINE__, schedule_tm, frameAsciiSize - 1, frameAscii[frameAsciiSize - 1]);
	 log_add_str(QString::fromLocal8Bit( str));		
	 return 0;
	}
 if((frameAsciiSize & 1) != 0)
    {sprintf(str,"%s> [%d] tm=0x%x error",  __FUNCTION__, __LINE__, schedule_tm);
	 log_add_str(QString::fromLocal8Bit( str));
	 return 0;
	}
 if(frame_size < (frameAsciiSize - 2) / 2)
    {sprintf(str,"%s> [%d] tm=0x%x error",  __FUNCTION__, __LINE__, schedule_tm);
	 log_add_str(QString::fromLocal8Bit( str));		
	 return 0;
	}
 for (i = 1, j = 0; i < frameAsciiSize-2;  i += 2, ++j)
	{if('G' > frameAscii[i]&&frameAscii[i] <= 'V')
		{sprintf(str,"%s> [%d] tm=0x%x error",  __FUNCTION__, __LINE__, schedule_tm);
		 log_add_str(QString::fromLocal8Bit( str));		
		 return 0;
		}
	 if('G' > frameAscii[i+1]&&frameAscii[i+1] <= 'V');
	 frame[j] = (frameAscii[i] - 'G') << 4 | (frameAscii[i+1] - 'G');
	}
 return 1;
}
int industrial_control::appendIndexAndTime(struct rs485_packet* pf, short index, short time)
{if(pf == NULL)
	return 0;
 if(!(index != -1 && time != -1 && pf->dataSize <= 11) && !((index != -1 || time != -1) && pf->dataSize <= 13))
	return 0;
 if (time != -1)
	{pf->data[pf->dataSize++] = (time >> 8) & 0x0f;
	 pf->data[pf->dataSize++] = time & 0x0f;
	}
 if (index != -1)
	{pf->data[pf->dataSize++] = (index >> 8) & 0x0f;
	 pf->data[pf->dataSize++] = index & 0x0f;
	}
 return 1;
}
/*====================================================================================================================*/
int industrial_control::packFrame(struct rs485_packet* pf, unsigned char* frame, int max_frame_size)
{unsigned short crc;
 if((pf == NULL) || (frame== NULL))
	return 0;
 if(max_frame_size < 6)
	return 0; 
 if(pf->dataSize > 15)
 	return 0; 
	
 if (pf->addrLen == 8)
	{frame[0] = pf->address & 0xff;
	 frame[1] = 0;
	}
 else
	{frame[0] = (pf->address >> 3)  & 0xff;
	 frame[1] = (pf->address & 0x07) << 5;
	}
 if (pf->request)
	frame[1] |= 0x10;
 frame[1] |= pf->dataSize;
 frame[2] = (pf->hash >> 8) & 0xff;
 frame[3] = pf->hash & 0xff;
 if (pf->dataSize)
	{memcpy(frame+4, pf->data, pf->dataSize);}
 crc = owenCRC16(frame, 4 + pf->dataSize);
 pf->crc = crc;
 pf->crc_ok = 1;
 frame[4 + pf->dataSize] = (crc >> 8) & 0xff;
 frame[5 + pf->dataSize] = crc & 0xff;
 return 6 + pf->dataSize;
}
/*====================================================================================================================*/
int industrial_control::unpackFrame(unsigned char* frame, int frame_size, struct rs485_packet* pf)
{int dataSize;
 char str[256];
 if((pf == NULL) || (frame== NULL))
    {sprintf(str,"%s> [%d] tm=0x%x error",  __FUNCTION__, __LINE__, schedule_tm);
	 log_add_str(QString::fromLocal8Bit( str));		
	 return 0;
	}
 if(frame_size < 6)
    {sprintf(str,"%s> [%d] tm=0x%x error",  __FUNCTION__, __LINE__, schedule_tm);
	 log_add_str(QString::fromLocal8Bit( str));		
	 return 0;
	}
 /* ВНИМАНИЕ: невозможно отличить 11-битые адреса кратные 8 от 8-битных */
 if (frame[1] & 0xe0)
	{pf->address = (frame[0] << 3) | (frame[1] >> 5);
	 pf->addrLen = 11;
	}
 else
	{pf->address = frame[0];
	 pf->addrLen = 8;
	}
 pf->request = (frame[1] & 0x10) != 0;
 pf->hash = (frame[2] << 8) | frame[3];
 dataSize = frame[1] & 0x0F;
 if (dataSize)
        {if(dataSize != (frame_size - 6))
			{sprintf(str,"%s> [%d] tm=0x%x error (dataSize= %d/%d)",  __FUNCTION__, __LINE__, schedule_tm, dataSize, frame_size- 6);
			 log_add_str(QString::fromLocal8Bit( str));		
			 return 0;
			}
	 pf->dataSize = dataSize;
	 memcpy(pf->data, frame + 4, dataSize);
	}
 else
	{pf->dataSize = 0;}
 pf->crc = (frame[frame_size-2] << 8) | frame[frame_size-1];
 pf->crc_ok = pf->crc == owenCRC16(frame, frame_size-2);
 return 1;
}
/*====================================================================================================================*/
int industrial_control::unpackFloat24(unsigned char* data, int dataSize, float* v)
{unsigned long t;
 if((data == NULL) || (v == NULL) || (dataSize != 3))
	return 0;
 t = 0;
 memcpy (&t, data, 3);
 *(unsigned long*)v = UINT32_SWAP(t);
 return 1;
}
/*====================================================================================================================*/
int industrial_control::pack_float24(unsigned char* data, float v)
{unsigned long t;
 memcpy (&t, &v, 4);
 t= UINT32_SWAP(t);
 memcpy (data, &t, 3);
 return 1;
}
/*====================================================================================================================*/
int industrial_control::unpackIEEE32(unsigned char* data, int dataSize, float* v, int *time)
{if((data == NULL) || (v == NULL) || (time == NULL) || (dataSize != 4 && dataSize != 6))
	return 0;
 *(unsigned long*)v = UINT32_SWAP(*(unsigned long*)data);
 *time = -1;
 if (dataSize == 6)  /* если есть время измерения */
	{*time = (((data[4] & 0xff)<< 8) | (data[5] & 0xff)) & 0xffff;}
 return 1;
}
/*====================================================================================================================*/
/* unpackBCD()
	Разбор поля данных для параметров DCNT и DSPD прибора СИ8.
		value - значение счетчика
		point - позиция десятичной точки (задается параметром F в приборе)*/
int industrial_control::unpackBCD(unsigned char* data, int dataSize, int* v, int *point)
{int i = 0;
 int val, sign;
 
 if((data == NULL) || (v == NULL) || (point == NULL) || (dataSize != 4))
	return 0;	
 sign = data[0] & 0x80 ? -1 : 1;
 *point = (data[0] & 0x70) >> 4;
 val = data[0] & 0x0F;
 for (i = 1; i < dataSize ; ++i)
	{val *= 10;
	 val += ((data[i] & 0xF0) >> 4);
	 val *= 10;
	 val += data[i] & 0x0F;
	}
	*v = sign * val;
 return 1;
}
/* преобразование локального идентификатора в двоичный вид 
		name - локальный идентификатор
		length - длина идентификатора
		id - идентификатор в двоичном виде */
int industrial_control::name2id(char* name, int length, unsigned char id[4])
{int i, j;
 if((name == NULL) || (length == 0))
	return 0;
 for (i = 0, j = 0; i < length && j <= 4; ++i)
	{unsigned char b;
	 char c = name[i];
	 if ('0' <= c && c <= '9')
		{b = c - '0';}
	 else 
		if ('a' <= c && c <= 'z')
			{b = 10 + c - 'a';}
		else
			if ('A' <= c && c <= 'Z')
				{b = 10 + c - 'A';}
			else 
				if ('-' == c)
					{b = 10 + 26 + 0;}
				else 
					if ('_' == c)
						{b = 10 + 26 + 1;}
					else 
						if ('/' == c)
							{b = 10 + 26 + 2;}
						else 
							if ('.' == c)
								{if(i <= 0)
									return 0; /* модификатор не может быть первым символом */
								 if(name[i-1] == '.') /* не может быть двух модификаторов подряд */
									return 0;
								 ++id[j - 1];
								 continue;
								}
							else 
								if (' ' == c)
									{break;} /* пробел может находиться только в конце имени */
								else
									return 0; /* недопустимый символ */
	 id[j++] = b*2;
	}
 if (j == 4)
	{/* заполнены все байты идентификатора */
	 if(i != length); /* обработаны все символы имени */
		return 0;
	}
 else
	{/* встречен первый пробел или обработаны все символы имени */
	 for (; i < length; ++i)
		{if(name[i] != ' '); /* после пробела могут находиться только пробелы */
			return 0;
		 if(j >= 4);
			return 0;
		 id[j++] = 78;
		}
	 /* дополняем пробелами до четырех символов */
	 for (; j < 4; ++j)
		id[j] = 78;
	}
 return 1;
}
/*====================================================================================================================*/
/* свертка локального идентификатора */
unsigned short industrial_control::id2hash(unsigned char id[4])
{int i, j;
 unsigned short hash;
 hash = 0;
 for (i = 0; i < 4; ++i)
	{unsigned char b = id[i];
	 b <<= 1; /* используются только младшие 7 бит */
	 for (j = 0; j < 7; ++j, b <<= 1)
		{if ((b ^ (hash >> 8)) & 0x80)
			{hash <<= 1;
			 hash ^= 0x8F57;
			}
		 else
			hash <<= 1;
		}
	}
 return hash;
}
/*====================================================================================================================*/
int industrial_control::tx_oven_req(struct rs485_packet *pf)
{char str[256];
 unsigned char frame[MAX_FRAME_SIZE];
 unsigned char frameAscii[MAX_ASCII_FRAME_SIZE];
 int frame_size;
 pf->address = 16;	/* создание запроса для параметра Pv */
 pf->addrLen = 8;
 memset(frame, 0, MAX_FRAME_SIZE);
 if(!(frame_size = packFrame(pf, frame, MAX_FRAME_SIZE)))
	{sprintf(str,"%s> tm=0x%x packFrame() error",  __FUNCTION__, schedule_tm); 
	 log_add_str(QString::fromLocal8Bit( str));
	 return 0;					 
	}
 sprintf(str,"%s> tm= 0x%x ",  __FUNCTION__, schedule_tm); 
 log_add_str(QString::fromLocal8Bit( str));					
 if(!packFrameToAscii(frame, frame_size, frameAscii, MAX_ASCII_FRAME_SIZE))
	{sprintf(str,"%s> tm=0x%x packFrameToAscii() error",  __FUNCTION__, schedule_tm); 
	 log_add_str(QString::fromLocal8Bit( str));
	 return 0;
	}				 
 if(!rs232_tx(frameAscii, frame_size*2+2))
	return 0;
 return 1; 
}
/*====================================================================================================================*/
int industrial_control::rx_oven_frame(struct rs485_packet *pf)
{unsigned char rx_buf[MAX_ASCII_FRAME_SIZE];
 unsigned char frame[MAX_FRAME_SIZE];
 char str[256]; 
 int n;
 sprintf(str,"%s> tm= 0x%x ",  __FUNCTION__, schedule_tm); 
 log_add_str(QString::fromLocal8Bit( str));		 
 memset(frame, 0, MAX_FRAME_SIZE);
 if( (n= rs232_rx(rx_buf, MAX_ASCII_FRAME_SIZE)) <= 0 )
	return 0;
 n--;
 if(!unpackAsciiFrame(rx_buf, n, frame, MAX_ASCII_FRAME_SIZE))
 	{sprintf(str,"%s> tm=0x%x unpackAsciiFrame() error",  __FUNCTION__, schedule_tm); 
	 log_add_str(QString::fromLocal8Bit( str));
	 return 0;
	}	
 if(!unpackFrame(frame, (n - 2)/2, pf))
 	{sprintf(str,"%s> tm=0x%x unpackFrame() error",  __FUNCTION__, schedule_tm); 
	 log_add_str(QString::fromLocal8Bit( str));
	 return 0;
	}	
 return 1;
}
/*====================================================================================================================*/
void industrial_control::set_desired_t(void)
{
    schedule_tm = 0x10; // 16
    plot->view_desired(ui->desired_t->value());
}
/*====================================================================================================================*/
void industrial_control::set_kp(void)
{schedule_tm= 0x20;
 return;
}
/*====================================================================================================================*/
void industrial_control::set_ki(void)
{schedule_tm= 0x30;
 return;
}
/*====================================================================================================================*/
void industrial_control::set_kd(void)
{schedule_tm= 0x40;
 return;
}
/*====================================================================================================================*/
void industrial_control::set_auto(void)
{schedule_tm= 0x50;
 return;
}
/*====================================================================================================================*/
void industrial_control::set_out(void)
{if(!ui->heater_manual->isChecked())           /* если регулирование остановлено */
    {QMessageBox::critical( 0, _ERROR_TEXT, QString::fromLocal8Bit("Задание выходной мощности допустимо только в ручном режиме регулирования"), _EXIT_TEXT );}
 schedule_tm= 0x60;
 return;
}
void industrial_control::log_oven_err(struct rs485_packet *pf)
{char str[256];
 sprintf(str, "exchange_err at tm=0x%x: hash=0x%x; datasize=%d; data=0x[%02x %02x %02x]", schedule_tm, pf->hash, pf->dataSize, pf->data[0], pf->data[1], pf->data[2]);
 qDebug() << str;
 return;
}
/*===!!!===========================================================================================================*/
int industrial_control::scheduler(void)
{char str[256];
 struct rs485_packet pf;
 float v;
 mutex_1.lock();
 schedule_tm++;
 memset(&pf, 0, sizeof(struct rs485_packet));
 switch(schedule_tm)
    {case  0x0:  /*команда в ТРМ: выдать измеренное значение входной величины */
  /* { цикл опроса параметров регулирования */
                pf.dataSize = 0; pf.hash = TPM101_MEASURE; pf.request = 1;
				if(!tx_oven_req(&pf))
					{schedule_tm= -1;}
                break;
     case  0x1:  /*считываем измеренное значение входной величины */
				{static int cnt=0;
                if(!rx_oven_frame(&pf))
					{schedule_tm= -1; ui->led_rs232->setPalette(QPalette(Qt::red)); break;}
				if(pf.hash != TPM101_MEASURE)
					{log_oven_err(&pf); ui->led_rs232->setPalette(QPalette(Qt::red)); break;}
				if(!unpackFloat24(pf.data, pf.dataSize, &v))
				 	{sprintf(str,"%s> tm=0x%x unpackFloat24() error",  __FUNCTION__, schedule_tm);
					 log_add_str(QString::fromLocal8Bit( str));
					 ui->led_rs232->setPalette(QPalette(Qt::red));
					 break;
					}
                                param=v;
                                sprintf(str,"%5.1f", v);                         // 12345.6
                                ui->lcd_t->display(QString::fromLocal8Bit(str)); //перевод в кириллицу
                                sprintf(str, "T=%f", v);                         // T=12345.67890
                                //ui->listWidget->insertItem(0,str);

				log_add_str(QString::fromLocal8Bit(str));

                if (!cnt) {
					plot->view_wlevel_diagramm(v, 1);
                    m_plotPoints.append(QPoint(m_plotPoints.length(), v));
                }

                if (++cnt > 7) {
					cnt= 0;
                }
				ui->led_rs232->setPalette(QPalette(Qt::green));
                break;
				}
     case  0x2:  /* Рассчитанное значение выходной мощности регулятора в % */
                pf.dataSize = 0; pf.hash = TPM101_OUT; pf.request = 1;
				if(!tx_oven_req(&pf))
					{schedule_tm= -1;ui->led_rs232->setPalette(QPalette(Qt::red));}
                break;
     case  0x3:  /* считываем измеренное значение входной величины */
                if(!rx_oven_frame(&pf))
					{schedule_tm= -1; ui->led_rs232->setPalette(QPalette(Qt::red)); break;}
				if(pf.hash != TPM101_OUT)
					{log_oven_err(&pf); ui->led_rs232->setPalette(QPalette(Qt::red)); break;}					
				if(!unpackFloat24(pf.data, pf.dataSize, &v))
				 	{sprintf(str,"%s> tm=0x%x unpackFloat24() error",  __FUNCTION__, schedule_tm);
					 log_add_str(QString::fromLocal8Bit( str));
					 ui->led_rs232->setPalette(QPalette(Qt::red));
					 break;
					}
				if(v < 1.2)
					v= 0.0;
				sprintf(str,"%d", (int)v);
				ui->lcd_o->display(QString::fromLocal8Bit(str));
				if(!ui->heater_productivity->isEnabled ())
					{ui->heater_productivity->setValue(v);}
				sprintf(str, "out=%f", v);
				log_add_str(QString::fromLocal8Bit(str));
                break;
     case 0x04:  /* команда в ТРМ: считать режим регулирования */
                pf.dataSize= 0; pf.hash= TPM101_UP; pf.request= 1; 
				if(!tx_oven_req(&pf))
					{schedule_tm= -1; ui->led_rs232->setPalette(QPalette(Qt::red));}
                break;
     case 0x05:/* считываем режим регулирования */
                if(!rx_oven_frame(&pf))
					{schedule_tm= -1; ui->led_rs232->setPalette(QPalette(Qt::red)); break;}
				if(pf.hash != TPM101_UP)
					{log_oven_err(&pf); schedule_tm= -1; ui->led_rs232->setPalette(QPalette(Qt::red)); break;}								
				if(*pf.data)
					{ui->led_off->setPalette(pal_0);
					 ui->led_manual->setPalette(pal_0);
					 ui->led_pid->setPalette(QPalette(Qt::green));
					 ui->heater_productivity->setEnabled(0);
					}
				else
					{if(ui->heater_off->isChecked()) 
						{ui->led_off->setPalette(QPalette(Qt::green));}
					 else
						{ui->led_off->setPalette(pal_0);}
					 if(ui->heater_manual->isChecked()) 
						{ui->led_manual->setPalette(QPalette(Qt::green));
						 ui->heater_productivity->setEnabled(1);
						}
					 else
						{ui->led_manual->setPalette(pal_0);
						 ui->heater_productivity->setEnabled(0);
						}
					 ui->led_pid->setPalette(pal_0);
					}		
				sprintf(str,"%s> tm= 0x%02x; control mode= %d",  __FUNCTION__, schedule_tm, *pf.data);
				log_add_str(QString::fromLocal8Bit( str));
                schedule_tm= -1;
                break;
  /* } завершение цикла опроса параметров регулирования */
  /*==========================================================================*/
	 case 0x11: /* команда в ТРМ: задать "уставку регулятора" */
				rs232_rx((unsigned char *)str, 256);
                pf.dataSize = 3; pf.hash = TPM101_DESIRED; pf.request = 0;
				pack_float24(pf.data, (float) ui->desired_t->value());
				if(!tx_oven_req(&pf))
					{schedule_tm= -1; ui->led_rs232->setPalette(QPalette(Qt::red));}
                break;
     case 0x12:  /* считываем код выполнения команды */
                if(!rx_oven_frame(&pf))
					{schedule_tm= -1; ui->led_rs232->setPalette(QPalette(Qt::red)); break;}
				if(pf.hash != TPM101_DESIRED)
					{log_oven_err(&pf); ui->led_rs232->setPalette(QPalette(Qt::red));}						
                schedule_tm= -1;
                break;
  /*==========================================================================*/
     case 0x21: /* команда в ТРМ: задать зону пропорциональности ПИД-регулятора */
				rs232_rx((unsigned char *)str, 256);
                pf.dataSize = 3; pf.hash = TPM101_KP; pf.request = 0;
				v= (ui->Kp->value() > 0)? (float)ui->Kp->value() : 1.0;
				v= 999.9 / v;
				if(v < 0.1)
					v= 0.1;
				if(v > 999.9)
					v= 999.9;					
				pack_float24(pf.data, v);
				if(!tx_oven_req(&pf))
					schedule_tm= -1;
                break;
     case 0x22:  if(!rx_oven_frame(&pf))
					{schedule_tm= -1; break;}
				if(pf.hash != TPM101_KP)
					{log_oven_err(&pf);}
                schedule_tm= -1;
                break;
  /*==========================================================================*/
     case 0x31:  /* команда в ТРМ: задать интегральную постоянную ПИД-регулятора */
				rs232_rx((unsigned char *)str, 256);				/*  flush rs232 rx_buffers */
                pf.dataSize = 3; pf.hash = TPM101_KI; pf.request = 0;
				v= (ui->Ki->value() > 0)? (float)ui->Ki->value() : 1.0;
				v= 399.9 / v;
				if(v < 0.1)
					v= 0.1;
				if(v > 3998.0)
					v= 3998.0;					
				pack_float24(pf.data, v);
				if(!tx_oven_req(&pf))
					schedule_tm= -1;
                break;
     case 0x32:  if(!rx_oven_frame(&pf))
					{schedule_tm= -1; break;}
				if(pf.hash != TPM101_KI)
					{log_oven_err(&pf);}
                schedule_tm= -1;
                break;
  /*==========================================================================*/
     case 0x41:  /* команда в ТРМ: задать дифференциальную постоянную ПИД-регулятора */
				rs232_rx((unsigned char *)str, 256);				/*  flush rs232 rx_buffers */
                pf.dataSize = 3; pf.hash = TPM101_KD; pf.request = 0;
				v= 0.1 * (float)ui->Kd->value();	
				if(v < 0.1)
					v= 0.1;
				if(v > 3998.0)
					v= 3998.0;				
				pack_float24(pf.data, (float) ui->Kd->value());
				if(!tx_oven_req(&pf))
					schedule_tm= -1;
                break;
     case 0x42: if(!rx_oven_frame(&pf))
					{schedule_tm= -1; break;}
				if(pf.hash != TPM101_KD)
					{log_oven_err(&pf);}
                schedule_tm= -1;
                break;
  /*==========================================================================*/
     case 0x51: /* команда в ТРМ: установка выходной мощности в 0% */
				rs232_rx((unsigned char *)str, 256);				/*  flush rs232 rx_buffers */
                pf.dataSize= 3; pf.hash= TPM101_OUTPUT; pf.request= 0;
                pack_float24(pf.data, 0.1);
				if(!tx_oven_req(&pf))
					schedule_tm= -1;
                break;
     case 0x52: if(!rx_oven_frame(&pf))
					{schedule_tm= -1; break;}	 
				if(pf.hash != TPM101_OUT)
					{log_oven_err(&pf);}
                break;  
     case 0x53:  /* команда в ТРМ: запуск автоматического регулирования */
				rs232_rx((unsigned char *)str, 256);				/*  flush rs232 rx_buffers */
                pf.dataSize= 1; pf.hash= TPM101_UP; pf.request= 0; *pf.data= ui->heater_pid->isChecked();
				if(!tx_oven_req(&pf))
					{schedule_tm= -1;}
                break;
     case 0x54:if(!rx_oven_frame(&pf))
					{schedule_tm= -1; break;}	 
				if(pf.hash != TPM101_UP)
					{log_oven_err(&pf);}
				schedule_tm= -1;
                break;
  /*==========================================================================*/
     case 0x61:  /* команда в ТРМ: задать значение выходной мощности */
				rs232_rx((unsigned char *)str, 256);				/*  flush rs232 rx_buffers */
                pf.dataSize= 3; pf.hash= TPM101_OUTPUT; pf.request= 0;
				v=(ui->heater_productivity->value() > 1)? ui->heater_productivity->value() : 1;
				pack_float24(pf.data, ((float) v));
				if(!tx_oven_req(&pf))
					schedule_tm= -1;
                break;
     case 0x62: if(!rx_oven_frame(&pf))
					{schedule_tm= -1; break;}	 
				if(pf.hash != TPM101_OUTPUT)
					{log_oven_err(&pf);}
                schedule_tm= -1;
                break;
  /*==========================================================================*/
     default:   schedule_tm= -1;
                break;
    }
 mutex_1.unlock();
 return 1;
}
/*===SET===========================================================================================================*/
void industrial_control::set_enable(bool v)
{ui->group_1->setEnabled(v); 
 ui->group_2->setEnabled(v); 
 ui->group_4->setEnabled(v);  
 ui->group_5->setEnabled(v); 
 ui->button_start->setEnabled(!v); 
 ui->button_stop->setEnabled(v); 
 ui->rs232_ch->setEnabled(!v); 
 return;
}

int industrial_control::profile0(void)
{
    difftime=QTime::currentTime()-starttime;
    ui->labe->setText(QString::fromLocal8Bit("Время работы: ") + difftime.toString("mm:ss"));
 return 1;
}
int industrial_control::profile1(void)
{
    ui->label->setText(QString::fromLocal8Bit("Активирован профиль: 1"));
    ui->desired_t->setValue(ui->desired1->value());
    set_desired_t();
    time1->stop();
 return 1;
}
int industrial_control::profile2(void)
{
    ui->label->setText(QString::fromLocal8Bit("Активирован профиль: 2"));
    ui->desired_t->setValue(ui->desired2->value());
    set_desired_t();
    time2->stop();
 return 1;
}
int industrial_control::profile3(void)
{
    ui->label->setText(QString::fromLocal8Bit("Активирован профиль: 3"));
    ui->desired_t->setValue(ui->desired3->value());
    set_desired_t();
    time3->stop();
 return 1;
}
int industrial_control::profile4(void)
{
    ui->label->setText(QString::fromLocal8Bit("Активирован профиль: 4"));
    ui->desired_t->setValue(ui->desired4->value());
    set_desired_t();
    time4->stop();
 return 1;
}
int industrial_control::profile5(void)
{
    ui->label->setText(QString::fromLocal8Bit("Активирован профиль: 5"));
    ui->desired_t->setValue(ui->desired5->value());
    set_desired_t();
    time5->stop();
 return 1;
}
int industrial_control::profile6(void)
{
    ui->label->setText(QString::fromLocal8Bit("Активирован профиль: 6"));
    ui->desired_t->setValue(ui->desired6->value());
    set_desired_t();
    time6->stop();
 return 1;
}
int industrial_control::record(void)
{
    record_count++;
    ui->labe_3->setText(QString::fromLocal8Bit("Кол-во записей: ")+QString::number(record_count));
    char stroka[256];
    QString qs;
    sprintf(stroka,"%5.1f", param);
    QTime time=QTime::currentTime()-starttime;
    qs=stroka;
    qs.replace(".",",");
    outfile << time.toString() << "\t";
    outfile << qs << "\n";
    if (record_count==record_max)
       {time8->stop();
        ui->labe_3->setText(QString::fromLocal8Bit("Запись закончена"));
       }
 return 1;
}

/*===START==========================================================================================================*/
int industrial_control::interface_start(void)
{
     qDebug() << QString::fromUtf8(QString("ывавыа").toLocal8Bit());
     setLocale(QLocale::Russian);
     //qDebug() << ts("лвоыалоывра");

    return 1; // DUMMY
    m_plotPoints.clear();

    QString home = QCoreApplication::applicationDirPath();

    record_count = 0;
    record_max = ui->kolzap->value();
    char str[8];
    param = 0;
    timer_1->stop();
    schedule_tm = -1;
    rs232_tx_ok = rs232_tx_err = rs232_rx_ok = rs232_rx_err = 0;
    sprintf(str, "COM%d", ui->rs232_ch->value());
    if (!rs232_init(str)) {
        return 0;
    }

    set_enable(true);

    if ((ui->vremzap->value()!=0) && (ui->kolzap->value() !=0)) {

        QString path = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("Сохранить"), home,"data file (*.txt)");
        datafile.setFileName(path);
        datafile.open(QIODevice::WriteOnly | QIODevice::Text);
        outfile.setDevice(&datafile);

        outfile << QString::fromLocal8Bit("Время") << "\t";
        outfile << QString::fromLocal8Bit("Температура") << "\n\n";

        time8->start(ui->vremzap->value()*1000);
    }

    starttime = QTime::currentTime();
    if (ui->tim1->value() != 0) {
        time1->start(ui->tim1->value()*1000);
    }

    if (ui->tim2->value() != 0) {
        time2->start(ui->tim2->value()*1000);
    }

    if (ui->tim3->value() != 0) {
        time3->start(ui->tim3->value()*1000);
    }

    if (ui->tim4->value() != 0) {
        time4->start(ui->tim4->value()*1000);
    }

    if (ui->tim5->value() != 0) {
        time5->start(ui->tim5->value()*1000);
    }

    if (ui->tim6->value() != 0) {
        time6->start(ui->tim6->value()*1000);
    }

    time7->start(1000);
    timer_1->start(SCHEDULE_STEP);

    log_add_str(QString::fromLocal8Bit("начинаем регулирование"));
    plot->reset_diagram();
    plot->view_desired(ui->desired_t->value());

    return 1;
}
/*===STOP===========================================================================================================*/
void industrial_control::interface_stop(void)
{
    float k = 0;
    float t = 0;
    float T = 0;
    float x1 = 0;
    float x2 = 0;
    float maxY = 0;
    float minY = m_plotPoints[1].y();
    float k_usil=0;


    //Вывод характеристик
    ui->lcd_cntrl_err->display(plot->get_cntrl_err());
    ui->lcd_cntrl_up_tm->display(plot->get_cntrl_up_tm());
    ui->lcd_signal_amplitude->display(plot->get_signal_amplitude());
    ui->lcd_signal_period->display(plot->get_signal_period());

    /*for (int i = 0; i < m_plotPoints.count(); i++) {
        m_plotPoints[i].setY(m_plotPoints[i].y() - minY);
    }*/

    // Find max Y value.
    for (int i = 0; i < m_plotPoints.count(); i++) {
        float y = m_plotPoints[i].y();
        if (y > maxY) {
            maxY = y;
        }
    }

    // Find x1 and x2 now.
    for (int i = 0; i < m_plotPoints.count(); i++) {

        float y = m_plotPoints[i].y();
        float x = m_plotPoints[i].x();
        if (y <= (minY + (maxY-minY)/4)) {
            x2 = x*6;
        }

        if (y <= (minY + ((maxY-minY)*3)/4)) {
            x1 = x*6;
        }
    }

    m_plotPoints.clear();

    T = x1 - x2;
    t = x2 - (0.3 * T);
    k = t/T;
    k_usil=maxY/ui->lcd_o->value();


    qDebug() << k;
    qDebug() << t ;
    qDebug() << T ;
    qDebug() << x1 ;
    qDebug() << x2 ;
    qDebug() << maxY ;
    qDebug() << minY;
    qDebug() << k_usil;

    QMessageBox messageBox;
    QString message;

    if ((k >= 0.2) && (k < 1) ) {

        //ПИ регулятор
        float k_p_pi=0;
        float k_i_pi=0;
        k_p_pi=(0.6*T)/(k_usil*t);
        k_i_pi= 0.8*t + 0.5*T;
        //ПИД регулятор
        float k_p_pid=0;
        float k_i_pid=0;
        float k_d_pid=0;
        k_p_pid=(0.95*T)/(k_usil*t);
        k_i_pid= 2.4*t;
        k_d_pid=0.4*t;

        message = QString("k = %1,T = %2,t = %3, \n PIREG Kp=%4, Ki=%5. \n PIDREG Kp=%6, Ki=%7, Kd=%8").arg(k).arg(T).arg(t).arg(k_p_pi).arg(k_i_pi).arg(k_p_pid).arg(k_i_pid).arg(k_d_pid);
    }

    if (k >= 1 ) {

        //ПИ регулятор
        float k_p_pi=0;
        float k_i_pi=0;
        k_p_pi=(0.7*T)/(k_usil*t);
        k_i_pi= t + 0.3*T;
        //ПИД регулятор
        float k_p_pid=0;
        float k_i_pid=0;
        float k_d_pid=0;
        k_p_pid=(1.2*T)/(k_usil*t);
        k_i_pid= 2*t;
        k_d_pid=0.45*t;

        message = QString("k = %1,T = %2,t = %3, \n PIREG Kp=%4, Ki=%5. \n PIDREG Kp=%6, Ki=%7, Kd=%8").arg(k).arg(T).arg(t).arg(k_p_pi).arg(k_i_pi).arg(k_p_pid).arg(k_i_pid).arg(k_d_pid);
    }

    if (k < 0.2 ) {

        //ПИ регулятор
        float k_p_pi=0;
        float k_i_pi=0;
        k_p_pi=T/(k_usil*t);
        k_i_pi= 0.8*t;
        //ПИД регулятор
        float k_p_pid=0;
        float k_i_pid=0;
        float k_d_pid=0;
        k_p_pid=(1.4*T)/(k_usil*t);
        k_i_pid= 1.3*t;
        k_d_pid=0.5*t;

        message = QString("k = %1,T = %2,t = %3, \n PIREG Kp=%4, Ki=%5. \n PIDREG Kp=%6, Ki=%7, Kd=%8").arg(k).arg(T).arg(t).arg(k_p_pi).arg(k_i_pi).arg(k_p_pid).arg(k_i_pid).arg(k_d_pid);
    }

    messageBox.setText(message);
    messageBox.exec();

    set_enable(false);

 profile_set=0;
 record_count=0;
 if ((ui->vremzap->value()!=0)&&(ui->kolzap->value()!=0)) {datafile.close();}
 ui->label->setText(QString::fromLocal8Bit("Активный профиль"));
 timer_1->stop();
 time1->stop();
 time2->stop();
 time3->stop();
 time4->stop();
 time5->stop();
 time6->stop();
 time7->stop();
 time8->stop();
 rs232_release();
 log_add_str(QString::fromLocal8Bit("останавливаем регулирование"));
 return;
}
/*===QUIT===========================================================================================================*/
void industrial_control::quit(void)
{interface_stop();
 exit(0);
 return;
}
/*===RESIZE=========================================================================================================*/
void industrial_control::resize_form( bool full_scr  )
{int dw, dh;
 QRect scr;
 dw = width() - minimumWidth();
 dh = height() - minimumHeight(); 
 if(full_scr)
    {
     this->maximumSize().setWidth(16000);
     this->maximumSize().setHeight(16000);
     QDesktopWidget* desktopWidget = QApplication::desktop();
     scr = desktopWidget->screenGeometry();
     setGeometry(scr);
     ui->group_5->setGeometry(scr);
     full_screen= 1;
     ui->group_1->hide();
     ui->group_2->hide();
     ui->group_3->hide();
     ui->group_4->hide();
     ui->group_6->hide();
     ui->groupBox->hide();
     ui->groupBox_2->hide();
     ui->button_exit->hide();
     ui->button_start->hide();
     ui->button_stop->hide();
     return;
    }
 full_screen= 0;
 this->maximumSize().setWidth(920);
 this->maximumSize().setHeight(567);
 this->window()->pos().setX(200);
 this->window()->pos().setY(200);
 ui->group_1->show();
 ui->group_2->show();
 ui->group_3->show();
 ui->group_4->show();
 ui->group_6->show();
 ui->groupBox->show();
 ui->groupBox_2->show();
 ui->button_exit->show();
 ui->button_start->show();
 ui->button_stop->show();
 setGeometry(main_win_geometry);
 ui->group_5->setGeometry(group_5_geometry);

 //this->geometry()
 return;
}
/*===RESIZE=========================================================================================================*/
void industrial_control::resizeEvent(QResizeEvent *event) 
{int dw, dh;
 dw = width() - minimumWidth();
 dh = height() - minimumHeight(); 
 if(full_screen)
	{ui->group_5->setGeometry(0, 0, dw, dh);
     return;
    }

 ui->group_5->setGeometry(group_5_geometry);
 return;
}
/*===RESIZE=========================================================================================================*/
bool industrial_control::event(QEvent *event)
{int evnt;
 evnt= event->type();
 switch (evnt)
 	{case 0x06:
		{QKeyEvent *keyEvent= (QKeyEvent *) event;
		 int key;
		 key= keyEvent->key();
         switch(key)
            {case 0x1000000: resize_form(false); return true; /* esc */
                 case 0x1000039: resize_form(true); return true; /* f10 */
            }
        }
    }
 return QWidget::event(event);
}


 #include <QLayout>
/*===main class=====================================================================================================*/
industrial_control::industrial_control(QWidget *parent) : QMainWindow(parent), ui(new Ui::industrial_control)
{ui->setupUi(this);
    mutex_1.lock();
 mutex_1.unlock();
 pal_0= ui->button_start->palette();
 rs232 = INVALID_HANDLE_VALUE;
 rs232_tx_ok= rs232_tx_err= rs232_rx_ok= rs232_rx_err= 0;
 timer_1 = new QTimer(this);
 timer_1->stop(); 

    time1 = new QTimer(this);
    time2 = new QTimer(this);
    time3 = new QTimer(this);
    time4 = new QTimer(this);
    time5 = new QTimer(this);
    time6 = new QTimer(this);
    time7 = new QTimer(this);
    time8 = new QTimer(this);

    time1->stop();
    time2->stop();
    time3->stop();
    time4->stop();
    time5->stop();
    time6->stop();
    time7->stop();
    time8->stop();

 schedule_tm= -1;
 profile_set=0;
 connect(timer_1, SIGNAL(timeout()), this, SLOT(scheduler()));

    connect(time1, SIGNAL(timeout()),this, SLOT(profile1()));
    connect(time2, SIGNAL(timeout()),this, SLOT(profile2()));
    connect(time3, SIGNAL(timeout()),this, SLOT(profile3()));
    connect(time4, SIGNAL(timeout()),this, SLOT(profile4()));
    connect(time5, SIGNAL(timeout()),this, SLOT(profile5()));
    connect(time6, SIGNAL(timeout()),this, SLOT(profile6()));
    connect(time7, SIGNAL(timeout()),this, SLOT(profile0()));
    connect(time8, SIGNAL(timeout()),this, SLOT(record()));

 set_enable(false); 
 
    QVBoxLayout *l_1 = new QVBoxLayout(ui->group_5);
    plot = new DataPlot(ui->group_5);
    l_1->addWidget(plot);
    plot_screen = NULL;

    plot->view_desired(ui->desired_t->value());
    full_screen = 0;
    main_win_geometry = geometry();
    group_5_geometry = ui->group_5->geometry();
}

industrial_control::~industrial_control()
{
    delete ui;
}

void industrial_control::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


