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

#include <IfxPort.h>
#include <LQ_GPIO.h>
#include <LQ_GPIO_KEY.h>
#include <LQ_GPIO_LED.h>
#include <LQ_STM.h>
#include <LQ_TFT18.h>
#include <stdio.h>
#include <LQ_RDA5807.h>

unsigned short RXFreq = 9450;

/*************************************************************************
*  �������ƣ�void RDA5807_Reset()
*  ����˵����RDA5807 �����λ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��      RDA5807_Reset();
*************************************************************************/
void RDA5807_Reset(void)
{
	RDA5807_WriteReg(RDA_R02,0x0002|RDA5807_ReadReg(RDA_R03)); //�����λ
	delayms(55);
}


/*************************************************************************
*  �������ƣ�void RDA5807_SetFreq(unsigned short freq)
*  ����˵����RDA5807 ��������Ƶ��
*  ����˵����freq   �� ����Ƶ��  ��Χ 6500~10800
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��RDA5807_SetFreq(9500);   //��������Ƶ��  95.0Mhz
*************************************************************************/
void RDA5807_SetFreq(unsigned short freq)
{
  unsigned short temp;
  unsigned char  spc = 0,band = 0;
  unsigned short fbtm, chan;

  temp = RDA5807_ReadReg(RDA_R03);
  temp &= 0x001F;
  band = (temp>>2) & 0x03;
  spc = temp & 0x03;
  if(spc == 0)
  {
	  spc=10;
  }
  else if(spc == 1)
  {
	  spc=20;
  }
  else
  {
	  spc=5;
  }

  if(band == 0)
  {
	  fbtm=8700;
  }
  else if(band==1||band==2)
  {
	  fbtm=7600;
  }
  else
  {
    fbtm = RDA5807_ReadReg(0x53);
    fbtm *= 10;
  }

  if(freq<fbtm)
  {
	  return;
  }
  chan = (freq - fbtm)/spc;
  chan &= 0x3FF;
  temp |= chan<<6;
  temp |= 1<<4;
  RDA5807_WriteReg(RDA_R03, temp) ;
  delayms(55);
}

/*************************************************************************
*  �������ƣ�void RDA5807_Enable(unsigned char flag)
*  ����˵����RDA5807 ʹ��
*  ����˵����flag   �� 1 ʹ��оƬ 0 ����оƬ
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��RDA5807_Enable(1);//1 ʹ��оƬ
*************************************************************************/
void RDA5807_Enable(unsigned char flag)
{
  unsigned short temp;
  temp=RDA5807_ReadReg(RDA_R02);
  if(flag ==1 )
    temp |=1;
  if(flag == 0)
    temp &= ~0x1;
  RDA5807_WriteReg(RDA_R02,temp);
  delayms(200);
}
/*************************************************************************
*  �������ƣ�unsigned char RDA5807_GetRssi(void)
*  ����˵������ȡRSSI
*  ����˵������
*  �������أ��ź�ǿ�Ȼ�ȡ0~127
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��RDA5807_Enable(1);   //ʹ��RDA5807
*************************************************************************/
unsigned char RDA5807_GetRssi(void)	//�ź�ǿ�Ȼ�ȡ		0~127
{
  unsigned short temp=0;
  temp=RDA5807_ReadReg(0x0B);
  temp=(temp>>9)&0x7f;
  return  ((unsigned char)temp);
}
/*************************************************************************
*  �������ƣ�void RDA5807_SetVol(unsigned char vol)
*  ����˵����RDA5807 ʹ��
*  ����˵����vol  ��������	 0~15
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��RDA5807_SetVol(12);	                   //��������0~15
*************************************************************************/
void RDA5807_SetVol(unsigned char vol)	//��������	 0~15
{
  unsigned short temp=0;
  temp=RDA5807_ReadReg(RDA_R05);
  temp&=0xfff0;
  RDA5807_WriteReg(RDA_R05,vol|temp) ;
  delayms(55);
}
/*************************************************************************
*  �������ƣ�void RDA5807_SetMute(unsigned char mute)	//�������� 1Ϊ����	0Ϊ������
*  ����˵����RDA5807 ��������
*  ����˵����mute)	�������� 1Ϊ����	0Ϊ������
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��RDA5807_SetMute(1);	                   //1Ϊ����
*************************************************************************/
void RDA5807_SetMute(unsigned char mute)	//�������� 1Ϊ����	0Ϊ������
{
  unsigned short temp=0;

  temp=RDA5807_ReadReg(0x02);
  if(!mute)
  {
	  RDA5807_Init();
	  RDA5807_SetFreq(RXFreq);
  }
  else
  {
	  temp&=0xBFFF;
	  RDA5807_WriteReg(RDA_R02,temp) ;
	  RDA5807_Reset(); //�����λ
  }
}

/*************************************************************************
*  �������ƣ�void RDA5807_SetSeekth(unsigned short rssi)
*  ����˵����RDA5807 //�Զ���̨�ź���ֵǿ��
*  ����˵����rssi 0~15 Ĭ��Ϊ8  ��ֵԽ���ѵ���̨Խ��
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��RDA5807_SetSeekth(5);	//�Զ���̨�ź���ֵǿ��0~15 Ĭ��Ϊ5  ��ֵԽ���ѵ���̨Խ��
*************************************************************************/
void RDA5807_SetSeekth(unsigned short rssi)	   //�Զ���̨�ź���ֵǿ��		0~15 Ĭ��Ϊ8  ��ֵԽ���ѵ���̨Խ��
{
  unsigned short temp;
  rssi = rssi & 0xf;
  temp=RDA5807_ReadReg(0x05);
  temp&=~(0xf<<8);
  temp|= rssi<<8;
  RDA5807_WriteReg(RDA_R05,temp) ;
  delayms(55);
}

/*************************************************************************
*  �������ƣ�void RDA5807_Init()
*  ����˵����RDA5807 ��ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��
*************************************************************************/
void RDA5807_Init(void)
{
  FMI2C_Init();
  RDA5807_Enable(1);//�ϵ�ʹ��
  RDA5807_Reset();  //�����λ
  RDA5807_WriteReg(RDA_R02,0xd281); //����ѡ��32.768Khz ���������ص���������
  delayms(50);
  RDA5807_WriteReg(RDA_R03,0x0500); //Ƶ����Ϊ87.5MHz ������100Khz Ƶ��Ϊ87M~108M
  delayms(50);
  RDA5807_WriteReg(RDA_R04,0x0040); //��������
  delayms(20);
  RDA5807_WriteReg(RDA_R05,0x8886); //��������Ϊvol=6 ������ֵΪ8
  delayms(20);
  RDA5807_SetVol(12);	                   //��������0~15
  RDA5807_SetSeekth(5);	               //�Զ���̨�ź���ֵǿ��0~15 Ĭ��Ϊ5  ��ֵԽ���ѵ���̨Խ��
}

/*************************************************************************
*  �������ƣ�void Test_RDA5807()
*  ����˵����RDA5807 ����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��4��10��
*  ��    ע��
*************************************************************************/
void Test_RDA5807(void)
{
  char txt[16];
  unsigned char  Key_num=0,Vol=10,RSSI=0,mute=1;


  RDA5807_Init();	      //RDA5807��ʼ��
  GPIO_KEY_Init();

  TFTSPI_Init(1);         //LCD��ʼ��  0:����  1������
  TFTSPI_CLS(u16BLACK);   //��ɫ��Ļ

  //��ʾоƬID 0x5804
  RXFreq = RDA5807_ReadReg(RDA_R00);
  sprintf(txt,"Chip:0x%04X",RXFreq);
  TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ

  RSSI=RDA5807_GetRssi();//��ʾ�ź�ǿ��0~127
  sprintf(txt,"RSSI:%02d  ",RSSI);
  TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ

  //��������Ƶ�� 90.50
  RXFreq=9050;
  RDA5807_Reset();  //�����λ
  RDA5807_SetFreq(RXFreq);
  sprintf(txt,"Freq:%d.%02dMHz ",RXFreq/100,RXFreq%100);
  TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ

  //��ʾ����
  sprintf(txt,"Volm:%02d  ",Vol);
  TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ

  TFTSPI_P8X16Str(3,1,"FM Radio",u16WHITE,u16BLACK);//�ַ�����ʾ

  while (1)
  {
	RSSI = RDA5807_GetRssi();//��ʾ�ź�ǿ��0~127
	sprintf(txt,"RSSI:%02d  ",RSSI);
	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
    Key_num = KEY_Read_All();;
    switch(Key_num)
    {
        case 3: 			     //KEY0 KEY1 ͬʱ����������
          if(Vol == 0)
            Vol = 0;
          else
            Vol -= 1;
          RDA5807_Init();
          RDA5807_SetVol(Vol);
          RDA5807_SetFreq(RXFreq);
          sprintf(txt,"Volm:%02d  ",Vol);
          TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
          break;
        case 6:
          if(Vol == 15) Vol = 15; 	 //KEY2 KEY1 ͬʱ����������
          else Vol += 1;
          RDA5807_Init();
          RDA5807_SetVol(Vol);
          RDA5807_SetFreq(RXFreq);
          sprintf(txt,"Volm:%02d  ",Vol);
          TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
          break;

		case 1:        //KEY0 ����  Ƶ�ʼ�
		  if(RXFreq == 8700) RXFreq = 10800;
		  else RXFreq -= 10;
		  RDA5807_Reset();
		  RDA5807_SetFreq(RXFreq);
		  sprintf(txt,"Freq:%d.%02dMHz ",RXFreq/100, RXFreq%100);
		  TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
		  break;

		case 2:	                 //KEY1 ����  Ƶ��95.0
		  RXFreq = 9500;
		  RDA5807_Reset();
		  RDA5807_SetFreq(RXFreq);
		  sprintf(txt,"Freq:%d.%02dMHz ",RXFreq/100, RXFreq%100);
		  TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
		  break;

		case 4:        //KEY2 ����  Ƶ�ʼ�
		  if(RXFreq == 10800) RXFreq = 8700;
		  else RXFreq += 10;
		  RDA5807_Reset();
		  RDA5807_SetFreq(RXFreq);
		  sprintf(txt,"Freq:%d.%02dMHz ",RXFreq/100, RXFreq%100);
		  TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
		  break;

		case 7:        //KEY012 ͬʱ����
		      if(mute==1)			//����
		      {
		        RDA5807_SetMute(1);
		        TFTSPI_P8X16Str(1,6,"Mute:Yes!",u16WHITE,u16BLACK);		//�ַ�����ʾ
		        mute=0;
		      }
		      else
		      {
		        RDA5807_SetMute(0);
		        TFTSPI_P8X16Str(1,6,"Mute:No! ",u16WHITE,u16BLACK);		//�ַ�����ʾ
		        mute=1;
		      }
		      break;

		default:
		  break;
    }
    LED_Ctrl(LED0,RVS);        //��ƽ��ת,LED��˸
    delayms(100);              //��ʱ�ȴ�
  }
}





/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////RDA5807M �ײ�IIC����/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////



void FMI2C_delay()        //����FMI2C��ʱ
{
  unsigned short  i = 0;
  for(i = 0; i <2000; i++) //�޸�������Ե���FMI2C����
  {
      __asm("NOP"); /* delay */
  }
}
/*************************************************************************
*  �������ƣ�void FMI2C_Init(void)
*  ����˵����ģ��FMI2C��ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  Ӧ�þ�����FMI2C_Init();  //ģ��FMI2C��ʼ�� FMI2C�ܽ���LQ_SOFTI2C.h�ж���
*************************************************************************/
void FMI2C_Init(void)
{
  FMI2C_SCL_INIT;
  FMI2C_SDA_INIT;
  FMI2C_SCL_H;
  FMI2C_SDA_H;
}

void FMI2Cstart() 		//FMI2C�����ź�
{
  FMI2C_SDA_H;
  FMI2C_SCL_H;
  FMI2C_delay();
  FMI2C_delay();
  FMI2C_SDA_L;
  FMI2C_delay();
  FMI2C_SCL_L;
}
void FMI2Cstop()			//FMI2Cֹͣ�ź�
{
  FMI2C_SCL_L;
  FMI2C_SDA_L;
  FMI2C_delay();
  FMI2C_delay();
  FMI2C_SCL_H;
  FMI2C_delay();
  FMI2C_SDA_H;
  FMI2C_delay();
}

unsigned char FMI2C_Wait_Ack(void)	//FMI2C�����ֽں� �ȴ��ӻ�������Ӧ��
{
  unsigned short ucErrTime=0;

  FMSDA_IN;             //SDA����Ϊ����ģʽ �ȴ����մӻ���������
  FMI2C_SDA_H;
  FMI2C_delay();
  FMI2C_SCL_H;
  FMI2C_delay();
  while(FMI2C_SDA_READ)
  {
    ucErrTime++;
    if(ucErrTime>10000)
    {
      FMSDA_OUT;
      FMI2Cstop();
      return 1;
    }
  }
  FMI2C_SCL_L;
  FMSDA_OUT;
  return 0;
}
void FMI2C_Ack(void)	  //����Ӧ���ź�
{
  FMI2C_SCL_L;
  FMI2C_SDA_L;		  //0������?��|��e
  FMI2C_delay();
  FMI2C_SCL_H;
  FMI2C_delay();
  FMI2C_SCL_L;
}

void FMI2C_NAck(void)	 //FMI2C ��Ӧ���ź�
{
  FMI2C_SCL_L;
  FMI2C_SDA_H;
  FMI2C_delay();
  FMI2C_SCL_H;
  FMI2C_delay();
  FMI2C_SCL_L;
}
void FMI2CsendByte(unsigned char txd)		 //FMI2C?дһ���ֽ�
{
  unsigned char t;
  FMI2C_SCL_L;
  for(t=0;t<8;t++)
  {
    if(txd&0x80)
      FMI2C_SDA_H;
    else
      FMI2C_SDA_L;
    txd<<=1;
    FMI2C_delay();
    FMI2C_SCL_H;
    FMI2C_delay();
    FMI2C_SCL_L;
    FMI2C_delay();
  }
  FMI2C_delay();
}
unsigned char FMI2CReadByte(unsigned char ack)  //FMI2C��һ���ֽ�
{
  unsigned char i,receive=0;
  //FMI2C_SDA_H;		  //��Ƭ���������ø߿���Ϊ��������
  FMSDA_IN;             //SDA����Ϊ����ģʽ �ȴ����մӻ���������
  FMI2C_delay();
  for(i=0;i<8;i++ )
  {
    FMI2C_SCL_L;
    FMI2C_delay();
    FMI2C_SCL_H;
    receive<<=1;
    if(FMI2C_SDA_READ) receive++;
    FMI2C_delay();
  }
  FMSDA_OUT;
  if (!ack)
    FMI2C_NAck();
  else
    FMI2C_Ack();
  return receive;
}
unsigned short RDA5807_ReadReg(unsigned char regAddr)			//оƬ���Ĵ���
{
  unsigned short buf;
  FMI2Cstart();
  FMI2CsendByte(RDA_WRITE);	  //����оƬ��ַ ����Ϊд
  FMI2C_Wait_Ack();
  FMI2CsendByte(regAddr);	      //���ͼĴ�����ַ
  FMI2C_Wait_Ack();

  FMI2Cstart();
  FMI2CsendByte(RDA_READ); 	  // ����оƬ��ַ ����Ϊ��
  FMI2C_Wait_Ack();
  buf = FMI2CReadByte(1);
  buf = buf<<8;
  buf =buf|FMI2CReadByte(0);
  FMI2Cstop();
  return buf;
}


void RDA5807_WriteReg(unsigned char regAddr,unsigned short val) //оƬд�Ĵ���
{
  FMI2Cstart();
  FMI2CsendByte(RDA_WRITE);	//����оƬ��ַ ����Ϊд
  FMI2C_Wait_Ack();
  FMI2CsendByte(regAddr);	    //���ͼĴ�����ַ
  FMI2C_Wait_Ack();
  FMI2CsendByte(val>>8);
  FMI2C_Wait_Ack();
  FMI2CsendByte(val&0xFF);
  FMI2C_Wait_Ack();
  FMI2Cstop();
}
