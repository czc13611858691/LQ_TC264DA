/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC264DA核心板
【编    写】ZYF/chiusir
【E-mail  】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2020年10月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】AURIX Development Studio1.2.2及以上版本
【Target 】 TC264DA/TC264D
【Crystal】 20.000Mhz
【SYS PLL】 200MHz
________________________________________________________________
基于iLLD_1_0_1_11_0底层程序,

使用例程的时候，建议采用没有空格的英文路径，
除了CIF为TC264DA独有外，其它的代码兼容TC264D
本库默认初始化了EMEM：512K，如果用户使用TC264D，注释掉EMEM_InitConfig()初始化函数。
工程下\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c第164行左右。
________________________________________________________________
测试ADC函数，一般用几个MIC就开启几个ADC即可。
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include <LQ_ADC.h>
#include <LQ_GPIO_LED.h>
#include <LQ_OLED096.h>
#include <LQ_STM.h>
#include <LQ_UART.h>
#include <stdio.h>
#include <LQ_TFT18.h>
/*************************************************************************
*  函数名称：void TestADC(void)
*  功能说明：ADC采集测试
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：   ADC悬空不为零，随机的
*************************************************************************/
void Test_ADC(void)
{
    sint16 vbat;
    char txt[16];

    ADC_InitConfig(ADC0, 80000); //初始化
    ADC_InitConfig(ADC1, 80000);
    ADC_InitConfig(ADC2, 80000);
    ADC_InitConfig(ADC3, 80000);
    ADC_InitConfig(ADC4, 80000);
    ADC_InitConfig(ADC5, 80000);
    ADC_InitConfig(ADC6, 80000);
    ADC_InitConfig(ADC7, 80000);

    OLED_Init();
    OLED_P6x8Str(0,0,"adc test");
    while(1)
    {
        vbat=ADC_Read(ADC0);
        vbat = vbat * 2 / 25;  // x/4095*3.3*100*5.7
        sprintf(txt, "bat : %d.%02dV", vbat / 100, vbat % 100);           //转换为字符串
        OLED_P6x8Str(0,2,txt);                      //显示采样时间
        vbat=ADC_Read(ADC1);
        vbat = vbat * 2 / 25;  // x/4095*3.3*100*5.7
        sprintf(txt, "bat : %d.%02dV", vbat / 100, vbat % 100);           //转换为字符串
        OLED_P6x8Str(0,3,txt);                      //显示采样时间
        vbat=ADC_Read(ADC2);
        vbat = vbat * 2 / 25;  // x/4095*3.3*100*5.7
        sprintf(txt, "bat : %d.%02dV", vbat / 100, vbat % 100);           //转换为字符串
        OLED_P6x8Str(0,4,txt);                      //显示采样时间
        vbat=ADC_Read(ADC3);
        vbat = vbat * 2 / 25;  // x/4095*3.3*100*5.7
        sprintf(txt, "bat : %d.%02dV", vbat / 100, vbat % 100);           //转换为字符串
        OLED_P6x8Str(0,5,txt);

    }

}
/*************************************************************************
*  函数名称：void Test_ADC_TFT(void)
*  功能说明：ADC采集测试在TFT1.8上显示
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：   ADC悬空不为零，随机的
*************************************************************************/
void Test_ADC_TFT(void)
{
  sint16 vbat;
  char txt[16];

  ADC_InitConfig(ADC0, 80000); //初始化
  ADC_InitConfig(ADC1, 80000);
  ADC_InitConfig(ADC2, 80000);
  ADC_InitConfig(ADC3, 80000);
  ADC_InitConfig(ADC4, 80000);
  ADC_InitConfig(ADC5, 80000);
  ADC_InitConfig(ADC6, 80000);
  ADC_InitConfig(ADC7, 80000);

  TFTSPI_Init(1);        //LCD³õÊ¼»¯  0:ºáÆÁ  1£ºÊúÆÁ
  TFTSPI_CLS(u16BLUE);   //À¶É«ÆÁÄ»
  while(1)
  {
    vbat=ADC_Read(ADC0);
    vbat = vbat * 2 / 25;  // x/4095*3.3*100*5.7
    sprintf(txt, "Bat:%d.%02dV ", vbat / 100, vbat % 100);  // *3.3/4095*3
    TFTSPI_P8X16Str(3, 3, txt, u16PURPLE, u16BLACK);   // ×Ö·û´®ÏÔÊ¾


    vbat=ADC_Read(ADC1);
    vbat = vbat * 2 / 25;  // x/4095*3.3*100
    sprintf(txt, "ch4:%d.%02dV ", vbat / 100, vbat % 100);  // *3.3/4095
    TFTSPI_P8X16Str(3, 4, txt, u16PURPLE, u16BLACK);   // ×Ö·û´®ÏÔÊ¾


    vbat=ADC_Read(ADC2);
    vbat = vbat * 2 / 25;  // x/4095*3.3*100
    sprintf(txt, "ch5:%d.%02dV ", vbat / 100, vbat % 100);  // *3.3/4095
    TFTSPI_P8X16Str(3, 5, txt, u16PURPLE, u16BLACK);   // ×Ö·û´®ÏÔÊ¾

    vbat=ADC_Read(ADC3);
    vbat = vbat * 2 / 25;  // x/4095*3.3*100
    sprintf(txt, "ch5:%d.%02dV ", vbat / 100, vbat % 100);  // *3.3/4095
    TFTSPI_P8X16Str(3, 6, txt, u16PURPLE, u16BLACK);   // ×Ö·û´®ÏÔÊ¾

    LED_Ctrl(LED0,RVS);
    delayms(100);
  }

}
/*************************************************************************
*  函数名称：void Test_Beacon7mic(void)
*  功能说明：采集测试6+1麦克风阵列
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：    ADC悬空不为零
*************************************************************************/
void Test_ADC_7mic(void)
{
    char txt[200];
    unsigned int MICVmin[8];

    ADC_InitConfig(ADC0, 80000); //初始化
    ADC_InitConfig(ADC1, 80000); //初始化
    ADC_InitConfig(ADC2, 80000); //初始化
    ADC_InitConfig(ADC3, 80000); //初始化
    ADC_InitConfig(ADC4, 80000); //初始化
    ADC_InitConfig(ADC5, 80000); //初始化
    ADC_InitConfig(ADC6, 80000); //初始化
    ADC_InitConfig(ADC7, 80000); //初始化   如果使用龙邱母板  则测分压后的电池电压，具体可以看母板原理图
    delayms(500);                //延时等待
	UART_PutStr(UART0,"\n-------------------------------------------------\n");//分界线
	while(1)
	{
		MICVmin[0]=ADC_Read(ADC0);
		MICVmin[1]=ADC_Read(ADC1);
		MICVmin[2]=ADC_Read(ADC2);
		MICVmin[3]=ADC_Read(ADC3);
		MICVmin[4]=ADC_Read(ADC4);
		MICVmin[5]=ADC_Read(ADC5);
		MICVmin[6]=ADC_Read(ADC6);
		MICVmin[7]=ADC_Read(ADC7);

		//转换结果为字符串，串口发送或者屏幕显示
		sprintf(txt,"[0]:%05d  [1]:%05d  [2]:%05d  [3]:%05d  [4]:%05d  [5]:%05d  [6]:%05d  [7]:%05d  \r\n",MICVmin[0],MICVmin[1],MICVmin[2],MICVmin[3],MICVmin[4],MICVmin[5],MICVmin[6],MICVmin[7]);
		//串口发送到上位机
		UART_PutStr(UART0,txt);//AN0--AN7十进制数据输出到上位机


    	LED_Ctrl(LED0,RVS);        //电平翻转,LED闪烁
		delayms(500);              //延时等待
	}
}
//
