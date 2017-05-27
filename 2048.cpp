//2048!!!
#include<iostream>
#include<conio.h>
#include<iomanip>
#include<dos.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<stdio.h>
using namespace std;
struct highscores					//for storing highscores in a binary file
{
    int scores;
    char names[20];
};
struct node							//for storing the matrix to use undo
{
	int m[4][4];
	int sc;
	node* next;
};
node *top=0;
void push(int a[4][4],int sco)		//PUSHING the matrix in a stack
{
	node *tmp=new node;
	if(tmp)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				tmp->m[i][j]=a[i][j];
			}
		}
		tmp->sc=sco;
		tmp->next=top;
		top=tmp;
	}
}
int pop(int a[4][4],int &sco)		//POPING the matrix from the stack	
{
	node *tmp=top;
	if(tmp)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				a[i][j]=tmp->m[i][j];
			}
		}
		sco=tmp->sc;
		top=top->next;
		delete tmp;
	}
	else
	  return 0;
}
int main()
{
    system("cls");
    unsigned char b,b1;
    char name[20];
    int a[4][4];
    int z;
    do
    {
		system("cls");
		int i,j,k,c,ch=1,flag=1,score=0;
		for(i=0;i<10;i++)
		cout<<"\n";
		cout<<"\t\t\t\t2048 PUZZLE !!!!\n\n";
		cout<<"\t\t\t\t1 - PLAY NOW!!!\n";
		cout<<"\t\t\t\t2 - INSTRUCTIONS\n";
		cout<<"\t\t\t\t3 - HIGH SCORES\n";
		cout<<"\t\t\t\t4 - EXIT\n";
		cout<<"\t\t\t\tEnter a number from 1-4:";
		cin>>z;
		system("cls");
		if(z==2)
		{
			cout<<"Use arrow key to move the numbers. When two same numbers touch, they merge! You win when you reach 2048!!!\n\n";
			cout<<"Enter to go back";
			cin.get();
			cin.get();
			system("cls");
		}
		else if(z==3)	
		{
			ifstream fin("highscores.dat",ios::binary);
			highscores h;
			int e=1;
			if(fin)
			{
			     fin.read((char*)&h,sizeof(h));
			     cout<<"\n\n"<<setw(15)<<"S.NO"<<setw(15)<<"NAME"<<setw(11)<<"SCORE\n";
			     while(!fin.eof())
			     {
				   cout<<setw(15)<<e<<setw(15)<<h.names<<setw(10)<<h.scores<<"\n";
				   fin.read((char*)&h,sizeof(h));
				   e++;
			     }
			}
			else
				cout<<"NO HIGH SCORES!!";
			cin.get();
			cin.get();

		}
	    else if(z==1)
	    {
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
	        		a[i][j]=0;
		    i=rand()%4;				//random number generation
		    j=rand()%4;
		    a[i][j]=2;
		    score=0;
			while(flag==1)
		    {
				system("cls");
				if(ch==1)
				{
					k=rand()%4+1;
					if(k<=2)
					    k=2;
					else
					    k=4;
					do
					{
					   i=rand()%4;
					   j=rand()%4;
					 }while(a[i][j]!=0);
					 a[i][j]=k;
					 
				}
				push(a,score);
	   	        cout<<"SCORE: "<<score;
	   	        cout<<"\t\t\tPress U for undo!!";
			 	cout<<"\t    Press esc to exit!!\n";
				for(i=0;i<10;i++)
					cout<<"\n";
				for(i=0;i<4;i++)
				{
				    cout<<setw(30);
				    for(j=0;j<4;j++)
				    {
					    if(a[i][j]==0)
							cout<<"O"<<setw(8);
					    else
							cout<<a[i][j]<<setw(8);
					}
					cout<<"\n\n";
				}
				ch=0;
					b=getch();
					     b1=b;
					     if(b1==72)					//72 is the ascii value for UP arrow
					     {
						     for(i=0;i<4;i++)
						     {
								j=0;
								int s[]={0,0,0,0};
								while(a[j][i]==0&&j<4)
								   j++;
								for(j;j<4;j++)
								{
								    if(a[j][i]!=0)
								    {
									    k=j;
									    while(k>=1&&a[k-1][i]==0)
									    {
										      a[k-1][i]=a[k][i];
										      a[k][i]=0;
										      k--;
										      ch=1;
									    }
									     if(k>=1&&a[k-1][i]==a[k][i]&&s[k-1]!=1)
									     {
											 a[k-1][i]*=2;
											 score+=a[k-1][i];
											 a[k][i]=0;
											 ch=1;
											 s[k-1]=1;
									     }
									 }
								}
							}
					     }
					     else if(b1==75)			//75 is the ascii value for LEFT arrow
					     {
						     for(i=0;i<4;i++)
						     {
								j=0;
								int s[]={0,0,0,0};
								while(a[i][j]==0&&j<4)
									j++;
								for(j;j<4;j++)
								{
									if(a[i][j]!=0)
									{
										for(k=j;k>0&&a[i][k-1]==0;k--)
										{
											a[i][k-1]=a[i][k];
											a[i][k]=0;
											ch=1;
										}
										if(k>0&&a[i][k-1]==a[i][k]&&s[k-1]!=1)
										{
											a[i][k-1]*=2;
											a[i][k]=0;
											score+=a[i][k-1];
											ch=1;
											s[k-1]=1;
										}
										}
								     }
						     }
					     }
						 else if(b1==77)			//77 is the ascii value for RIGHT arrow
					     {
						     for(i=0;i<4;i++)
						     {
								j=3;
								int s[]={0,0,0,0};
								while(j>=0&&a[i][j]==0)
									j--;
								for(j;j>=0;j--)
								{
									if(a[i][j]!=0)
									{
										for(k=j;a[i][k+1]==0&&k<3;k++)
										{
												a[i][k+1]=a[i][k];
												a[i][k]=0;
												ch=1;
										}
										if(k<3&&a[i][k]==a[i][k+1]&&s[k+1]!=1)
										{
											a[i][k+1]*=2;
											a[i][k]=0;
											score+=a[i][k+1];
											ch=1;
											s[k+1]=1;
										}
									}
								}
						     }
					     }
						 else if(b1==80)			//80 is the ascii value for DOWN arrow
					     {
							 for(i=0;i<4;i++)
							 {
								j=3;
								int s[]={0,0,0,0};
								while(a[j][i]==0&&j>=0)
									j--;
								for(j;j>=0;j--)
								{
									if(a[j][i]!=0)
									{
										for(k=j;a[k+1][i]==0&&k<3;k++)
										{
											a[k+1][i]=a[k][i];
											a[k][i]=0;
											ch=1;
										}
										if(a[k+1][i]==a[k][i]&&k<3&&s[k+1]!=1)
										{
											a[k+1][i]*=2;
											a[k][i]=0;
											ch=1;
											score+=a[k+1][i];
											s[k+1]=1;
										}
									}
								}
							 }
					     }
					     else if(b==27)				//27 is the ascii value for 'esc' key
					     {
							 	flag=0;
							 	break;
						 }
					    else if(b==117)				//117 is the ascii value for 'U' key
					     {
							pop(a,score);
							pop(a,score);
					     }
			
						 int co=0;
					     for(i=0;i<4;i++)
					     {
								for(j=0;j<4;j++)
								{
									if(a[i][j]==2048)
										flag=2048;
									if(a[i][j]!=0)
										co++;
								}
					     }
					     if(co==16)					// To check whether any move is left
					     {
					     	flag=0;
							for(int r=0;r<4&&flag!=1;r++)
							{
								for(int s=0;s<4&&flag!=1;s++)
								{
									if(a[r][s]==a[r-1][s]&&r>=1||a[r][s]==a[r][s-1]&&s>=1||a[r][s]==a[r+1][s]&&r<=3||a[r][s]==a[r][s+1]&&s<=3)
										flag=1;
								}
							}		
					 	}
			}
			if(flag==0)
				cout<<"\t\t\t\tGAME OVER!!!";
			else
				cout<<"\t\t\t\tYou WIN!!!!";
			cout<<"\n\n\t\t\t\tYOUR SCORE IS "<<score;
			cin.get();
			cout<<"\nEnter your name:";
			cin.getline(name,20);
			ifstream fin("highscores.dat",ios::binary);
			ofstream fout("temp.dat",ios::binary);
			highscores h;
			highscores p;
			strcpy(p.names,name);
			p.scores=score;
			int fl=1,count=0;
			if(fin)
			{
			     fin.read((char*)&h,sizeof(h));
			     while(!fin.eof()&&count<10)		// Fos storing only top 10 highscores
			     {
				   if(fl)
				   {
    				   if(h.scores>=score)
    				   {
    				      fout.write((char*)&h,sizeof(h));
    				      count++;
    				   }
    				   else
    				   {
	    					fout.write((char*)&p,sizeof(p));
	    					count++;
	    					fl=0;
							if(count<10)
	    					{
	    					     fout.write((char*)&h,sizeof(h));
	    					     count++;
	    					}
    				   }
                   }
                   else if(fl==0&&count<10)
                   {
                       fout.write((char*)&h,sizeof(h));
                       count++;
                   }
			       fin.read((char*)&h,sizeof(h));
			    }
			    if(fl==1&&count<10)
				    fout.write((char*)&p,sizeof(p));
			}
			else
			     fout.write((char*)&p,sizeof(p));
			fout.close();
			fin.close();
			remove("highscores.dat");
			rename("temp.dat","highscores.dat");
		}
		while(top)
		    pop(a,score);
	}while(z!=4);
	int score;
	for(int i=0;i<12;i++)
	   cout<<"\n";
	cout<<"\t\t\tDONE BY:-\n";
	cout<<"\t\t\t\tP SRINATH";
	cin.get();
	cin.get();
}
