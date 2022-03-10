/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��10��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��AURIX Development Studio1.2.2�����ϰ汾
��Target �� TC264DA/TC264D
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________
����iLLD_1_0_1_11_0�ײ����,

ʹ�����̵�ʱ�򣬽������û�пո��Ӣ��·����
����CIFΪTC264DA�����⣬�����Ĵ������TC264D
����Ĭ�ϳ�ʼ����EMEM��512K������û�ʹ��TC264D��ע�͵�EMEM_InitConfig()��ʼ��������
������\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c��164�����ҡ�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_RDA5807_H
#define __LQ_RDA5807_H

#include "LQ_GPIO.h"
#include "stdint.h"


//RDA �ļĴ�����ַ
#define RDA_R00		0x00  //����16��λ��ID =0x5800
#define RDA_R02		0x02  //DHIZ[15],DMUTE[14]����,MONO[13]����,BASS[12]�ص���,SEEKUP[9],SEEK[8],SKMODE[7],CLK_MODE[6:4]ʱ��Դѡ��,SOFTRESET[1]��λ,ENABLE[0]��Դʹ��
#define RDA_R03		0x03  //CHAN[15:6],TUNE[4],BAND[3:2],SPACE[1:0] ����Ƶ�� ���� ����
#define RDA_R04		0x04  //STCIEN[14],DE[11],I2Senable[6],
#define RDA_R05		0x05  //INT_MODE[15],SEEKTH[14:8](�趨�Զ������ź�ǿ�ȷ�ֵ),LNA_PORT_SEL[7:6]=0b10,LNA_ICSEL_BIT[5:4],VOLUME[3:0]����;
#define RDA_R0A		0x0A  //STC[14]seek complete SF[13]seek fail readchan[9:0]��ǰƵ��
#define RDA_R0B		0x0B  //RSSI[15:9],FM TRUE[8]��ǰƵ����һ����Ŀ̨

//IIC������ַ0010000B�����϶�д��־����0x22��д����0x23�����������ַ�ʽ���Ե�������Ӧ�ļĴ������������ҿ���ֱ�Ӷ�дÿһ���Ĵ�����
#define RDA_READ       0x23  //��RDA5807M��0x23
#define RDA_WRITE	   0x22  //дRDA5807M��0x22

#define SOFT_FMI2C_SCL_PIN   P00_1   /*!< P00_1  ��Ϊ SCL */
#define SOFT_FMI2C_SDA_PIN   P00_2   /*!< P00_2  ��Ϊ SDA */

#define FMSDA_OUT        PIN_Dir(SOFT_FMI2C_SDA_PIN, 1)
#define FMSDA_IN         PIN_Dir(SOFT_FMI2C_SDA_PIN, 0)

#define FMI2C_SCL_INIT   PIN_InitConfig(SOFT_FMI2C_SCL_PIN, PIN_MODE_OUTPUT, 1)
#define FMI2C_SDA_INIT   PIN_InitConfig(SOFT_FMI2C_SDA_PIN, PIN_MODE_OUTPUT, 1)

#define FMI2C_SCL_H      PIN_Write(SOFT_FMI2C_SCL_PIN, 1)
#define FMI2C_SCL_L      PIN_Write(SOFT_FMI2C_SCL_PIN, 0)

#define FMI2C_SDA_H      PIN_Write(SOFT_FMI2C_SDA_PIN, 1)
#define FMI2C_SDA_L      PIN_Write(SOFT_FMI2C_SDA_PIN, 0)

#define FMI2C_SDA_READ   PIN_Read(SOFT_FMI2C_SDA_PIN)


void Test_RDA5807(void);
void RDA5807_Init(void);
void RDA5807_Enable(unsigned char flag);
void RDA5807_SetFreq(unsigned short freq);
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////RDA5807M �ײ�IIC����/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void FMI2C_Init(void);
void RDA5807_WriteReg(unsigned char regAddr,unsigned short val);  //оƬд�Ĵ���
unsigned short RDA5807_ReadReg(unsigned char regAddr);			 //оƬ���Ĵ���
#endif
