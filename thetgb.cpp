// *****************************************************************************
//               T H E     H O T E L     M A N A G E M E N T
// *****************************************************************************

//==================================  Class  ===================================
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<process.h>
#define line "\n\t____________________________________________________________";


class HOTEL
{
	private:
	char food_item[40];                            // for restaura
	float food_price;                              //    "
	int sno;                                       //    "
	char pass[6];                                  //    "
	int dd,mm,yyyy;                                // for room book
	char c_name[30],r_type[30];                    //    "
	int room_no;                                   //    "
	float r_bill,r_price;                          //    "
	char f_type[30];                               // for facility
	float f_price,f_code;                          //    "

	int checkdate(int da,int mo,int yr)
	{
		if(mo>12 || mo==0)
			return 0;
		if(da>31 || da==0)
			return 0;
		if(yr==0)
			return 0;
		if(mo<=7)
		{
			if(mo%2==0)
			{
				if(mo==2)
				{
					if(yr%4==0)
					{
						if(da>29)
							return 0;
					}
					else if(da>28)
						return 0;
				}
				else if(da>30)
					return 0;
			}
			else if(da>31)
				return 0;
		}
		else
		{
			if(mo%2==0 && da>31)
				return 0;
			else if(mo%2!=0 && da>30)
				return 0;
		}
		return 1;
	}

	public:
	char pas[6];
	int Enter_Admin_Pass();                   // Password To Enter Admin Menu
	void Enter_Food();                        // function for restaura
	void Display_Food();                      //           "
	void Room_Book();                         // function for room book
	void Room_Status();                       //           "
	void Room_Bill();                         //           "
	int no_days(int,int,int,int,int,int);     //           "
	void Write_Fac(int);                      // function for facility
	void Read_Fac();                          //           "
	HOTEL()
	{
		strcpy(pass,"thetgb");
	}
	int GetSerial()
	{
		return sno;
	}
	float GetPrice()
	{
		return food_price;
	}
	int Getrno()
	{
		return room_no;
	}
}h;
//==============================  End Of Class  ================================


//============================  Admin Password()  ==============================
// -----------------------------------------------------------------------------
int HOTEL::Enter_Admin_Pass()
{
	cout<<"\n\n\t =========================999 666=========================";
	cout<<"\n                                  ( @ @ )";
	cout<<"\n                           ....o00o.(_).o00o...";
	cout<<line;
	cout<<"\n\n\n\t Hey ! Admin Menu Is Encrypted With Password.";
	cout<<"\n\n\t\t  PASSWORD : ";
	restart:
	int j,l,k,count=0,count1=0;
	for(j=0;j<50;j++)
	{
		unvalid:
		l=getch();
		if(((l>=33)&&(l<=126))||(l==8)||(l==13))
			pas[j]=l;
		else
			goto unvalid;
		if(pas[j]==13)
			break;
		else if(pas[j]==8)
		{
			gotoxy(30,11);
			clreol();                                                   //conio.h
			for(k=0;k<=50;k++)
				pas[j]='\0';
			goto restart;
		}
		else
		{
			cout<<"*";
			count++;
		}
	}
	for(int i=0;i<count;i++)
	{
		if(pas[i]!=pass[i])
		  count1++;
	}
	if(count1==0)
	  return 1;
	else
	  return 0;
}
// -----------------------------------------------------------------------------
//=========================  End Of Admin Password()  ==========================

//===============================  Restaura()  =================================
// -----------------------------------------------------------------------------
void HOTEL::Enter_Food()
	{
		cout<<"\n\n\t\t Enter Serial Number : ";
		cin>>sno;
		cout<<"\n\t\t Enter Name Of New Dish : ";
		gets(food_item);
		cout<<"\n\t\t Enter The Price Of Dish : ";
		cin>>food_price;
	}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void HOTEL::Display_Food()
	{
		cout<<"\n\n\t "<<sno<<".";
		cout<<"\t Dish :  "<<food_item;
		cout<<"\n\t\t Price : "<<food_price;
	}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Admin_Enter_Food()
{
	char opt;
	clrscr();

	ofstream out;
	out.open("hotel_restaura.dat",ios::app);
	cout<<line;
	cout<<"\n\n\t\t\tEnter Details Of Dishes To Be Added";
	cout<<line;
	do
	{
		cout<<endl;
		h.Enter_Food();
		out.write((char*)&h,sizeof(h));
		cout<<"\n\n\t Do You Want To Enter More Dishes (Y/N) ? : ";
		cin>>opt;
		cout<<line;
	}while(opt=='y' || opt=='Y');
	out.close();
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Display_Food_Menu()
{
	ifstream in;
	in.open("hotel_restaura.dat",ios::in);
	cout<<"\n\t [-------------------  Restaura Menu Card  -------------------]";
	while((!in.eof()) && (in.read((char*)&h,sizeof(h))))
	{
		h.Display_Food();
	}
	cout<<line;
	in.close();
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Buy_Food()
{
	clrscr();
	int order;
	char ch,cont,flag;
	float food_total=0;
	cout<<"\n\t\t        +-0ooo----------------------+   ";
	cout<<"\n\t\t        |                           |   ";
	cout<<"\n\t\t        |         - T G B -         |   ";
	cout<<"\n\t\t        |                           |   ";
	cout<<"\n\t\t        |  Multicuisine Restaurant  |   ";
	cout<<"\n\t\t        +------------Ooo------------+   ";
	cout<<endl;
	Display_Food_Menu();
	ifstream in;
	ofstream out;
	out.open("temp_restaura.dat",ios::out);
	order_more:
	flag='n';
	in.open("hotel_restaura.dat",ios::in);

		cout<<"\n\n\t What You Want To Order (1,2,3,....) : ";
		cin>>order;
		in.seekg(0);
		while(!in.eof())
		{
			in.read((char*)&h,sizeof(h));
			if(h.GetSerial()==order)
			{
				flag='y';
				food_total+=h.GetPrice();
				out.write((char*)&h,sizeof(h));
				break;
			}
		}
		if(flag=='n')
		{
			cout<<"\n\t  Please Enter Appropriate Dish Number..";
		}
	in.close();
		cout<<"\n\t Do You Want To Order More (Y/N) ? : ";
		cin>>cont;
	if(cont=='y' || cont=='Y')
		goto order_more;

	out.close();

	clrscr();
	in.open("temp_restaura.dat",ios::in);
	cout<<"\n\n\t[----------------------  T G B  -------------------------]";
	cout<<"\n\n\t                 -----    Bill    -----";
	in.seekg(0);
	while((!in.eof()) && (in.read((char*)&h,sizeof(h))))
	{
		h.Display_Food();
	}
	cout<<"\n\n\n\t\t\t TOTAL BILL : "<<food_total<<" Rs.";
	cout<<"\n\n\t\t   Please Give Us 20 Minutes To Serve You ...";
	cout<<"\n\n\t[--------------------------------------------------------]";
	in.close();

}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Admin_Delete_Food()
{
	int ser_no,flag1=0;char ans;

	trying:
	cout<<"\n\n\t Enter The Serial Number Of Dish To Be Removed  : ";
	cin>>ser_no;

	fstream in,out;
	in.open("hotel_restaura.dat",ios::in);
	out.open("temp1_restaura.dat",ios::out);

	in.seekg(0);
	while((!in.eof()) && (in.read((char*)&h,sizeof(h))))
	{
		if(h.GetSerial()==ser_no)
		{
			flag1=1;
			cout<<"\n\n\t ... Details Of Dish To Be Removed  ...";
			cout<<"\n\t----------------------------------------------------";
			h.Display_Food();
			cout<<"\n\t----------------------------------------------------";
			cout<<"\n\n\t Are You Sure You Want To Remove This Dish (y/n) : ";
			cin>>ans;
			if(ans=='n' || ans=='N')
			{
				out.write((char*)&h,sizeof(h));
			}
		}
		else
		{
			out.write((char*)&h,sizeof(h));
		}
	}
	if(!flag1)
	{
		cout<<"\n\n\t ERROR .. Dish You Were Searching Does Not Exist In Menu Card !";
		goto trying;
	}

	in.close();
	out.close();
	remove("hotel_restaura.dat");
	rename("temp1_restaura.dat","hotel_restaura.dat");

	in.open("hotel_restaura.dat",ios::in);
	cout<<line;
	cout<<"\n\n\t[---------------  MENU CARD  ---------------]";
	in.seekg(0);
	while((!in.eof()) && (in.read((char*)&h,sizeof(h))))
	{
		if(in.eof())
			break;
		h.Display_Food();
	}
	cout<<"\n\n\t[-------------------------------------------]";
	cout<<line;
	in.close();
}
// -----------------------------------------------------------------------------
//============================  End Of Restaura()  =============================

//=============================  Room Booking()  ===============================
// -----------------------------------------------------------------------------
int HOTEL::no_days(int d1,int m1,int y1,int d2,int m2,int y2)
{
	int days=0,i,j,ya=y1;
	int monthdays[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(y2<y1)
		return 0;
	else if(y2==y1)
	{
		if(m2<m1)
			return 0;
	}
	else if(m2==m1)
	{
		if(d2<d1)
			return 0;
	}
	if((d1==d2) && (m1==m2) && (y1==y2))
		return 1;
	if(y2>y1)
	{
		for(j=ya+1;j<y2;j++)
		{
			if(j%4==0)
				days+=366;
			else
				days+=365;
		}
		for(i=m1+1;i<=12;i++)
		{
			if((i==2) && (y1%4==0))
				days+=29;
			else
				days+=monthdays[i-1];
		}
		if((m1==2) && (y1%4==0))
			days+=29;
		else
			days+=monthdays[m1-1]-d1;
		for(i=1;i<m2;i++)
		{
			if((i==2) && (y1%4==0))
				days+=29;
			else
				days+=monthdays[i-1];
		}
		if((m2==2) && (y2%4==0))
			days+=29;
		else
			days+=d2;

		return days;
	}
	if(y1==y2)
	{
		if(m1==m2)
			return(d2-d1+1);
		for(i=m1+1;i<m2;i++)
		{
			if((i==2) && (y1%4==0))
				days+=29;
			else
				days+=monthdays[i-1];
		}
		if((m1==2) && (y1%4==0))
			days+=29;
		else
			days+=monthdays[m1-1]-d1;
		if((m2==2) && (y2%4==0))
			days+=29;
		else
			days+=d2;

		return days;
	}
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void HOTEL::Room_Book()
{
	int type;
	int ran;
	randomize();
	cout<<"\n\n\t\t Customer's Name : ";
	gets(c_name);
	date:
	cout<<"\n\n\t\t Enter Today's Date : ";
	cout<<"\n\t\t\t dd : ";    cin>>dd;
	cout<<"\n\t\t\t mm : ";    cin>>mm;
	cout<<"\n\t\t\t yyyy : ";    cin>>yyyy;
	if(!checkdate(dd,mm,yyyy))
	{
		cout<<"\n\n\t\t Please Enter Appropriate Date ...";
		goto date;
	}
	cout<<"\n\n\t     Please Select The Class Of Room You Want (1 - 4) ...";
	cout<<"\n\n\t\t 1. Luxury Grande Suite .                  3000/-";
	cout<<"\n\n\t\t 2. Luxury Superior Suite .                4500/-";
	cout<<"\n\n\t\t 3. Royale Suite .                         6000/-";
	cout<<"\n\n\t\t 4. President Suite .                      8000/- \n\t\t\t\t  =>";
	cin>>type;
	if(type==1)
	{
		ran=random(100)+101;
		strcpy(r_type,"Luxury Grande Suite");
		r_price=3000;
		room_no=ran;
		cout<<"\n\n\t       |____________  Room Number :- "<<room_no<<"  ____________|";
	}
	if(type==2)
	{
		ran=random(100)+201;
		strcpy(r_type,"Luxury Superior Suite");
		r_price=4500;
		room_no=ran;
		cout<<"\n\n\t       |____________  Room Number :- "<<room_no<<"  ____________|";
	}
	if(type==3)
	{
		ran=random(100)+301;
		strcpy(r_type,"Royale Suite");
		r_price=6000;
		room_no=ran;
		cout<<"\n\n\t       |____________  Room Number :- "<<room_no<<"  ____________|";
	}
	if(type==4)
	{
		ran=random(100)+401;
		strcpy(r_type,"President Suite");
		r_price=8000;
		room_no=ran;
		cout<<"\n\n\t       |____________  Room Number :- "<<room_no<<"  ____________|";
	}
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void HOTEL::Room_Status()
{
	cout<<line;
	cout<<"\n\n\t\t Room Number : "<<room_no;
	cout<<"\n\t\t Customer's Name : "<<c_name;
	cout<<"\n\t\t Date : "<<dd<<" / "<<mm<<" / "<<yyyy;
	cout<<"\n\t\t Room Type : "<<r_type;
	cout<<"\n\t\t Room Price : "<<r_price;
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void HOTEL::Room_Bill()
{
	int d,m,y;
	long int day;
	dat:
	cout<<"\n\n\t\t Enter Today's Date : ";
	cout<<"\n\t\t dd : ";   cin>>d;
	cout<<"\n\t\t mm : ";   cin>>m;
	cout<<"\n\t\t yyyy : ";   cin>>y;
	if(!checkdate(d,m,y))
	{
		cout<<"\n\n\t Please Enter Appropriate Date ....";
		goto dat;
	}
	day=no_days(dd,mm,yyyy,d,m,y);
	if(day<=0)
	{
		cout<<"\n\n\t Please Enter Appropriate Date ....";
		goto dat;
	}
	cout<<"\n\n\t\t No. Of Days You Stayed Here : "<<day;
	if(strcmp(r_type,"Luxury Grande Suite")==0)
		r_bill=3000*day;
	if(strcmp(r_type,"Luxury Superior Suite")==0)
		r_bill=4500*day;
	if(strcmp(r_type,"Royale Suite")==0)
		r_bill=6000*day;
	if(strcmp(r_type,"President Suite")==0)
		r_bill=8000*day;

	cout<<"\n\n\t\t Please Pay Us  -:  Rs. "<<r_bill<<" Only  :-";
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Checkin()
{
	clrscr();
	cout<<"\n\t ====================================================================";
	cout<<"\n\t                         Book A Guest Room                           ";
	cout<<"\n\t ====================================================================";

	ofstream out;
	out.open("hotel_room.dat",ios::app);
		h.Room_Book();
		out.write((char*)&h,sizeof(h));
		cout<<"\n\n\t\t The Room Successfully Booked !!!";
	out.close();
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Display_Room()
{
	ifstream in;
	in.open("hotel_room.dat",ios::in);
	clrscr();
	cout<<"\n\n --------------------- Booked Room Details -------------------------";
	cout<<"\n\n NOTE :- Full details of rooms are hidden due to security aspects."<<endl;
	in.seekg(0);
	while((!in.eof()) && (in.read((char*)&h,sizeof(h))))
	{
		cout<<"\n\t ==>  "<<h.Getrno();
		cout<<endl;
	}
	in.close();
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Checkout()
{
	int flag=0,rn;
	clrscr();
	rn:
	char conf='n';
	cout<<"\n\n\t\t Enter Your Room Number : ";
	cin>>rn;
	ifstream in;
	ofstream out;
	in.open("hotel_room.dat",ios::in);
	out.open("temp3.dat",ios::out);
	while((!in.eof()) && (in.read((char*)&h,sizeof(h))))
	{
		if(rn==h.Getrno())
		{
			flag=1;
			cout<<"\n\n\t\t Details Of Room Number "<<rn<<" Are ";
			h.Room_Status();
			cout<<line;
			cout<<"\n\n\t\t Are You Sure You Want To Leave The Room ? (Y/N) : ";
			cin>>conf;
			if(conf=='y' || conf=='Y')
			{
				h.Room_Bill();
			}
			else
				out.write((char*)&h,sizeof(h));
		}
		else
			out.write((char*)&h,sizeof(h));
	}
	remove("hotel_room.dat");
	rename("temp3.dat","hotel_room.dat");
	if(!flag)
	{
		cout<<"\n\n\t The Room Number You Enter Does Not Exist..";
		cout<<"\n\t Please Enter Appropriate Room Nuumber .";
		goto rn;
	}
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Admin_Room_Status()
{
	ifstream in;
	in.open("hotel_room.dat",ios::in);
	clrscr();
	cout<<"\n\t ---------------- Details Of Room Occupants ---------------";
	in.seekg(0);
	while((!in.eof()) && (in.read((char*)&h,sizeof(h))))
	{
      h.Room_Status();
	}
	in.close();
}
// -----------------------------------------------------------------------------
//=========================  End Of Room Booking()  ============================

//===============================  Facility()  =================================
// -----------------------------------------------------------------------------
void HOTEL::Write_Fac(int o)
{
	int ran;
	randomize();
	ran=random(500)+1;
	if(o==1)
	{
		strcpy(f_type,"Swimming Pool");
		f_price=300;
		f_code=ran;
	}
	if(o==2)
	{
		strcpy(f_type,"Game Zone");
		f_price=500;
		f_code=ran;
	}
	if(o==3)
	{
		strcpy(f_type,"Theatre");
		f_price=600;
		f_code=ran;
	}
	if(o==4)
	{
		strcpy(f_type,"Gym");
		f_price=200;
		f_code=ran;
	}
	if(o==5)
	{
		strcpy(f_type,"Bar");
		f_price=400;
		f_code=ran;
	}
	cout<<"\n\t\t Your Facility Code Is : "<<f_code;
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void HOTEL::Read_Fac()
{
	 cout<<"\n\n\t\t Facility Used : "<<f_type;
	 cout<<"\n\n\t\t Facility Code : "<<f_code;
	 cout<<"\n\n\t\t Price : "<<f_price<<" Rs.";
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void View_Fac()
{
	clrscr();
	cout<<"\n\n\t*************************************************************";
	cout<<"\n\t|               Facilities Recently Used                    |";
	cout<<"\n\t*************************************************************";
	ifstream in;
	in.open("hotel_fac.dat",ios::in);
	in.seekg(0);
	while((!in.eof()) && (in.read((char*)&h,sizeof(h))))
	{
		cout<<line;
		h.Read_Fac();
		cout<<line;
	}
	in.close();
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Save_Fac(int opt)
{
	int o=opt;
	ofstream out;
	out.open("hotel_fac.dat",ios::app);
	h.Write_Fac(o);
	out.write((char*)&h,sizeof(h));
	out.close();
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void Other_Fac()
{
	int opt;
	char more;
	clrscr();
	cout<<"\n\n\t =============================================================";
	cout<<"\n\t                 TGB's Special Facilities";
	cout<<"\n\t =============================================================";
	cout<<"\n\n\t      1. Swimming Pool ......................  Rs. 300/-";
	cout<<"\n\n\t      2. Game Zone ..........................  Rs. 500/-";
	cout<<"\n\n\t      3. Theatre ............................  Rs. 600/-";
	cout<<"\n\n\t      4. Gym ................................  Rs. 200/-";
	cout<<"\n\n\t      5. Bar ................................  Rs. 400/-";
	cout<<line;
	again:
	cout<<"\n\n\t\t Please Select Any Facility (1 - 5) : ";
	cin>>opt;
	if(opt>=1 && opt<=5)
		Save_Fac(opt);
	else
	{
		cout<<"\n\n\t Please Enter Appropriate Option ...";
		goto again;
	}
	cout<<"\n\n\t Do You Want To Use More Facilities ? (Y/N) : ";
	cin>>more;
	if(more=='y' || more=='Y')
		goto again;
}
// -----------------------------------------------------------------------------
//============================  End Of Facility()  =============================

//===============================  About Us()  =================================
// -----------------------------------------------------------------------------
void About_Us()
{
	char ch;
	ifstream in;
	in.open("about_us.txt",ios::in);
	in.seekg(0);
	while(in)
	{
		in.get(ch);
		if(ch=='\n')
			cout<<" ";
		if(ch==' ')
			cout<<" ";
		else
			cout<<ch;
	}
	in.close();
}
// -----------------------------------------------------------------------------
//===========================  End Of About Us()  ==============================

//================================  Intro( )  ==================================
// -----------------------------------------------------------------------------
void Intro()
{
	cout<<"\n\t  ||------------------------------------------------------------||";
	cout<<"\n\t  ||                                                            ||";
	cout<<"\n\t  ||               THE HOTEL MANAGEMENT SOFTWARE                ||";
	cout<<"\n\t  ||                                                            ||";
	cout<<"\n\t  ||            Software Designed And Developed By -            ||";
	cout<<"\n\t  ||                   => Vishal Pattni                         ||";
	cout<<"\n\t  ||                                                            ||";
	cout<<"\n\t  ||                                                            ||";
	cout<<"\n\t  ||              (THE MACROSOFT© SOFTWARE CORP.)               ||";
	cout<<"\n\t  ||                                                            ||";
	cout<<"\n\t  ||------------------------------------------------------------||";
	cout<<"\n\n\n\n\n\n\t  Submitted To :- Mrs. Hely Shah  (Computer Teacher)";
	cout<<"\n\n\n\n\t\t Press Enter To Continue ....";
	getch();
	clrscr();
	cout<<"\n\t  ||^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^||";
	cout<<"\n\t  ||       *                 *               *           *      ||";
	cout<<"\n\t  ||           *      THE   GRAND   BHAGAWATI       *           ||";
	cout<<"\n\t  ||    *                                             *        *||";
	cout<<"\n\t  ||       *               WELCOMES  YOU     *                  ||";
	cout<<"\n\t  ||          *     *            *               *           *  ||";
	cout<<"\n\t  ||                   *       _____         *            *     ||";
	cout<<"\n\t  ||                  _____   |     |    ____                   ||";
	cout<<"\n\t  ||                    |     |   __    |    |                  ||";
	cout<<"\n\t  ||                    |     |     |   | --<                   ||";
	cout<<"\n\t  ||                    |     |_____|   |____|                  ||";
	cout<<"\n\t  ||++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++||";
	cout<<"\n\n\n\t Press Enter To Continue ....";
	getch();
	cout<<endl;
	clrscr();
}
// -----------------------------------------------------------------------------
//=============================  End Of Intro()  ===============================

//===============================  Void Main  ==================================
// -----------------------------------------------------------------------------
void main()
{
	char a_or_c;
	int last_opt,opt5;;
	int a_ch,room_opt;
	int getpass;
	Intro();
	A_or_C:
	passs:
	clrscr();
	cout<<"\n\n\t Please Enter Following Login Details....\n";
	cout<<"\n\n\t >>>    Admin           -----   Enter 'A'";
	cout<<"\n\n\t >>>    Customer        -----   Enter 'C'";
	cout<<"\n\n\t >>>    Exit            -----   Enter 'X'\n\n\n\n\t\t\t\t\t ==>";
	cin>>a_or_c;
	if(a_or_c=='a' || a_or_c=='A')
	{
		clrscr();
		getpass=h.Enter_Admin_Pass();
		if(getpass==1)
		{
			admin_menu:
			clrscr();
			cout<<"\n\n\t ~~~~~~~~~~~~~~~~~~~ [ Admin Menu ] ~~~~~~~~~~~~~~~~~~~";
			cout<<"\n\n\t\t 1. Include New Dishes To Menu Card ..";
			cout<<"\n\n\t\t 2. Remove Any Dishes From Menu Card ..";
			cout<<"\n\n\t\t 3. Display Menu Card ..";
			cout<<"\n\n\t\t 4. View Details Of Room Occupants ..";
			cout<<"\n\n\t\t 5. Goto Admin - Customer Menu ..\n\n\t\t\t\t\t ==> (1 - 4) : ";
			cin>>a_ch;
			switch(a_ch)
			{
				case 1:
				Admin_Enter_Food();
				break;
				case 2:
				Admin_Delete_Food();
				break;
				case 3:
				Display_Food_Menu();
				break;
				case 4:
				Admin_Room_Status();
				break;
				case 5:
				goto A_or_C;
				default:
					cout<<"\n\n\t Please Select Appropriate Option ...";
					goto admin_menu;
			}
		}
		else
		{
			clrscr();
			cout<<line;
			cout<<"\n\n\t\t     |--------------------------------|";
			cout<<"\n\t\t     |        .. E R R O R ..         |";
			cout<<"\n\t\t     |      Incorrect Password        |";
			cout<<"\n\t\t     |--------------------------------|";
			cout<<line;
			cout<<"\n\n\n\t\t Press Enter To Continue ...";
			getch();
			goto passs;
		}
		cout<<"\n\n\n\t\t Press Enter To Continue ...";
		getch();
		clrscr();
		goto admin_menu;
	}
	else if(a_or_c=='c' || a_or_c=='C')
	{
		customer_menu:
		clrscr();
		cout<<"\n\n\t |_|_|_|-----************   T G B   ************-----|_|_|_|";
		cout<<"\n\n\t\t 1. Restaura ..";
		cout<<"\n\n\t\t 2. Guest Room ..";
		cout<<"\n\n\t\t 3. Other Facilities ..";
		cout<<"\n\n\t\t 4. About Us ..";
		cout<<"\n\n\t\t 5. Goto Admin - Customer Menu ..\n\n\t\t\t\t\t ==> (1 - 5) : ";
		cin>>a_ch;
		clrscr();
		switch(a_ch)
		{
			case 1:
				Buy_Food();
			break;
			case 2:
				cout<<"\n\n\t ============ TGB's LUXURIOUS GUEST ROOMS ============";
				cout<<"\n\n\t\t 1. Book A Room       (Check - In)..";
				cout<<"\n\n\t\t 2. Cancel A Room     (Check - Out)..";
				cout<<"\n\n\t\t 3. Rooms Already Booked..";
				cout<<"\n\n ===> NOTE : Charges Are Calculated Per Day ..";
				cout<<"\n\n\t\t Select Option Of Your Wish .. (1 - 3)  ";
				cin>>room_opt;
				switch(room_opt)
				{
					case 1:
					Checkin();
					break;
					case 2:
					Checkout();
					break;
					case 3:
					Display_Room();
					break;
					default:
					goto customer_menu;
				}
			break;
			case 3:
				cout<<"\n\n\t\t ======== Our Other Facilities ========";
				cout<<"\n\n\t\t   1.  Use Facilities .";
				cout<<"\n\n\t\t   2.  View Used Facilities .";
				cout<<"\n\n\t\t Select Option Of Your Wish .. (1 - 2)  ";
				cin>>opt5;
				switch(opt5)
				{
					case 1:
						Other_Fac();
						break;
					case 2:
						View_Fac();
						break;
					default:
						goto customer_menu;
				}
			break;
			case 4:
				About_Us();
				break;
			case 5:
			goto A_or_C;
			default:
				cout<<"\n\n\t Please Select Appropriate Option ...";
				goto customer_menu;
		}
		cout<<"\n\n\n\t\t Press Enter To Continue ...";
		getch();
		goto customer_menu;
	}
	else if(a_or_c=='x' || a_or_c=='X')
	{
		clrscr();
		cout<<"\n\n\t\t  ___________________________________________________";
		cout<<"\n\t\t  ||                                               ||";
		cout<<"\n\t\t  ||                  THANK YOU                    ||";
		cout<<"\n\t\t  ||           for using the software of           ||";
		cout<<"\n\t\t  ||                                               ||";
		cout<<"\n\t\t  ||             THE HOTEL MANAGEMENT              ||";
		cout<<"\n\t\t  ||                                               ||";
		cout<<"\n\t\t  ||                                               ||";
		cout<<"\n\t\t  ____________________________By - Pattni Vishal_____";
		exit(0);
	}
	else
		goto A_or_C;
}
// -----------------------------------------------------------------------------
//============================  End Of Void Main  ==============================

//========================  E N D  O F  P R O G R A M  =========================

