#include "pid.h"

PID pid; //存放PID算法所需要的数据

void PID_Init()
{
  pid.Sv=50;//用户设定温度
	pid.T=200;//PID计算周期
	
	pid.Kp=350;
  pid.Ti=1000000;//积分时间
	pid.Td=1000;//微分时间
	
	pid.pwmcycle=1000;//pwm周期1000
	pid.OUT0=1;
}

void PID_Calc()  //pid计算
{
	static u16 calc;
	calc++;
	float DelEk;
	float ti,ki;
	//	float Iout;
	//	float Pout;
	//	float Dout;
	float td;
	float kd;
	float out;
	if(calc<pid.T)  //计算周期未到
		return ;
	pid.Ek=pid.Sv-pid.Pv;   //得到当前的偏差值
	pid.Pout=pid.Kp*pid.Ek;      //比例输出

	pid.SEk+=pid.Ek;        //历史偏差总和

	DelEk=pid.Ek-pid.Ek_1;  //最近两次偏差之差

	ti=pid.T/pid.Ti;
	ki=ti*pid.Kp;
 
	pid.Iout=ki*pid.SEk*pid.Kp;  //积分输出

	td=pid.Td/pid.T;

	kd=pid.Kp*td;
 
	pid.Dout=kd*DelEk;    //微分输出

	out= pid.Pout+ pid.Iout+ pid.Dout;
 
 
	 if(out>pid.pwmcycle)
	 {
		pid.OUT=pid.pwmcycle;
	 }
	 else if(out<0)
	 {
		pid.OUT=pid.OUT0; 
	 }
	 else 
	 {
		pid.OUT=out;
	 }
	 
	pid.Ek_1=pid.Ek;  //更新偏差

	calc=0;
}












