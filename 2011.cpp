#include <stdio.h>
#include <stdlib.h>
int i,j,x,num,c,d;
int m=13;
int  a[13][13];                        //------------------定义数组
char b[13][13];
void printsz(char arry[][13]);
void kong();
int main()
{
/*------------------------------------------------------------数组定义模块---------------------------------------------------------------------------*/	
   
	printf("  这个程序目前可以显示周围雷数，但是不能让周围非雷的空白自动翻开,里面有一段屏蔽的代码不知道为什么会报错，希望老师帮我看看啦。。。\n\n");
	printf("请输入您需要设定的雷数(小于35)\n");                                //---------------------为啥小于35个？大于就不运行了。。。
	scanf("%d",&num);
	for(i=0;i<m;i++)                                                            //----------------------赋值地雷矩阵的数组
	{
		for(j=0;j<m;j++)
		{
		a[i][j]=0;
		
		}
	}
	for (x=1;x<=num;x++)                                                        
	{
		do
		{
			int d=rand();
			j=d%m;
			int c=rand();
			i=c%m;
		}while (a[i][j]!=0);                                                //-------------------定义地雷随机分布
		a[i][j]=10;
		a[i+1][j]++; a[i+1][j-1]++; a[i+1][j+1]++; a[i][j-1]++;                //--------------------定义周围雷的数目
		a[i][j+1]++; a[i-1][j-1]++; a[i-1][j+1]++; a[i-1][j]++;              
	}     

    for(i=0;i<m;i++)                                                           //-------------------定义输出打印的数组
	{ 
		for(j=0;j<m;j++)
		{
           b[i][j]='*';
		}
	}

      for(i=0;i<m;i++)                    
	  {
		         for(j=0;j<m;j++)

		         {
		          	if (j==m-1)printf(" %d\n",a[i][j]);
				    else       printf(" %d",a[i][j]);
				 }
	  }
	printsz(b);                                                                //-------------------------首次打印
			
/*------------------------------------------------------------------用户输入模块--------------------------------------------------------------------------*/


	 for (x=1;x<m*m-num;x++)                 
	{

		printf("请输入要翻开的雷的行和列(从1列1行开始)\n");
	    scanf("%d,%d",&i,&j);
        i=i-1;
		j=j-1;                                                                //-----------------使用户输入的坐标相对于数组坐标成立
	    if (a[i][j]>=10)
		{
		    b[i][j]='@';                                                      //-----------------选中雷后定义数组
		    printsz(b);                     
			

			printf ("中雷了，你输了。。。 \n\n ╯﹏╰\n\n\n\n");
			break;  
			
	    }
     	else 
		{
			if(a[i][j]!=0){b[i][j]=a[i][j]+48;printsz(b);}                    //--------------未选中雷输出形式
			else                                              
			{
			    b[i][j]='o';
		  /*    kong();        */                                            //!!! 老师，问下为啥调用这句后，出错？(只调用一个可以，全部就有问题了。）
                printsz(b);
			}
		}
	}
	if (x==m*m-num) printf("赢咯。。。");
	printf("made by mizy    ╮(╯▽╰)╭\n");
    
	return 0;
}
/*-----------------------------------------------------------调用函数----------------------------------------------------*/

void printsz(char arry[][13])                                                 //打印函数
{
      for(i=0;i<m;i++)                    
	  {
		         for(j=0;j<m;j++)

		         {
		          	if (j==m-1)printf(" %c\n",arry[i][j]);
				    else       printf(" %c",arry[i][j]);
				 }
	  }
}
void kong()                                                                  //翻开一个空块，同时翻开周围的空块
{     if(i>=m||j>=m) ;
      else
	  {
	  if(a[i+1][j]!=0&&i<m){b[i+1][j]=a[i+1][j]+48;}else {b[i][j]='o';i=i+1;kong();}              //若全部调用便会出错？
      /*if(a[i][j-1]!=0&&j<m){b[i][j-1]=a[i][j-1]+48;}else {b[i][j]='o';j=j-1;;kong();}
	  if(a[i-1][j]!=0&&i<m){b[i-1][j]=a[i-1][j]+48;}else {b[i][j]='o';i=i-1;;kong();}
	  if(a[i][j+1]!=0&&j<m){b[i][j+1]=a[i][j+1]+48;}else {b[i][j]='o';j=j+1;;kong();}*/
	  }
}