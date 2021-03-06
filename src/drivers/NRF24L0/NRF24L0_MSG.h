#ifndef _NRF24L0_MSG_H_
#define	_NRF24L0_MSG_H_

#include "key_event.h"


#define COM_LEN     2   //com命令占用的字节



//控制命令COM执行函数返回结果
//COM命令，需要执行对应的函数
//MSG消息，发送方主动通知，不需要执行任何函数
typedef	enum
{
    NRF_RESULT_FALSE = 0,					//假、失败、事件没发生
    NRF_RESULT_TRUE	= 1,					//真、成功、事件发生了
    NRF_RESULT_QUIT,					//退出

    NRF_RESULT_NULL,                    //不进行任何处理

    //接收数据
    NRF_RESULT_RX_NO,                   //没接收到数据
    NRF_RESULT_RX_VALID,            	//接收有效数据
    NRF_RESULT_RX_NOVALID,              //接收到数据，但无效


    /*** EVENT 事件 ***/
    //	NRF_RESULT_EVENT_FALSE,				//没事件发生，或传输事件数据有误
    //	NRF_RESULT_EVENT_FINIST,			//事件传输完毕
    //	NRF_RESULT_EVENT_CONTINUE,			//事件继续传输（多个事件发送了，需要继续传输）

} nrf_result_e;

//控制命令消息类型
typedef	enum
{
    ////////////////// COM命令 /////////////////////
    //需要校验接收的命令是否正确
    //发送的数据： XXX_COM ，~XXX_COM    后面继续发送需要发送的信息，由对应的执行函数进行处理

    //图像传输控制
    COM_IMG,		    //发送图像命令:控制命令后，就直接接图像数据

    //事件控制
    COM_EVENT_INFORM,	//控制事件消息通知（主动通知对方是否有事件发生，这里通知变量改变了，改变了的值的大小）


    /*  需要添加功能，请放入此位置  */


    COM_MAX		,		//最大控制命令数目													********************************

} crtl_e;



#define   NRF_MSG_send_state()			NRF_ISR_Tx_State()		    //查询发送状态
nrf_result_e    NRF_MSG_send(crtl_e     com, u8 *sendbuf);    		//发送数据，发送长度由com对应的函数决定
nrf_result_e    NRF_MSG_receive(crtl_e  *com, u8 *rebuf);   		//接收数据,并进行处理

extern u32 last_var_num;                                            //最后接收到的变量编号,方便上层软件进行控制
void save_var2buff(var_tab_e var_num, u8 *sendbuf);            //把需要发送的变量的数据写入到缓冲区








#endif	//_NRF24L0_MSG_H_