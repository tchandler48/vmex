USERID CMSUSER
    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
    #include <string.h>
    #include <ctype.h>
    #include <math.h>
    #include <time.h>

    double sum = 0;
    double avg = 0;
    double value;

    int maxm = INT_MIN;
    int minm = INT_MAX;
    int proc_cel = 0;
    int cnt = 0;
    int epos = 0;
    int mrow = 0;
    int mcol = 0;
    int rct = 0;		/* current rpow setting */
    int cct = 1;		/* current col setting */
    int row;
    int col;
    int x;
    int z1;
    int z2;
    int z3;
    int z4;
    int i;
    int j;
    int pi;
    int cmd_byte = 0;
    int pgm_byte = 0;
    int day, month, year;
    int hour, min, sec;
    int t,i1,j1,i2,j2,k,l,m,n,row,col;
    int jj,i9;

    char input[20];
    char cellnum[6];
    char varname[4];
    char wkspace[9];
    char *sub;
    char wk_row[4];
    char wk_row1[4];
    char ch;
    char wk_file[12];
    char *p;
    char *p1;
    char *p2;
    char sheet_nm[9];
    char wsp_name[9];
    char f_date[11];
    char f_mth[3];
    char f_day[3];
    char f_yr[5];
    char f_time[9];
    char f_hr[3];
    char f_min[3];
    char f_sec[3];

    double spreadsheet[99][26] = {0};
      char sheet[99][26][20]   = {0};
      char src[99][26][20]     = {0};
       int flag[99][26]        = {0};

      FILE *fp;

     double Expression(void);
       int IsAddop(char);
    double Term(void);
    double Factor(void);
      void Match(char);
       int IsAddop(char);
       int IsMultop(char);
       int Is_White(char);
      void SkipWhite(void);
      void _GetChar(void);
    double GetNum(void);
      void Save_wsp(void);
      void Load_wsp(void);
      void Prog_dsp(void);
      void Get_date(void);
      void Get_time(void);
      void Math_dsp(void);
      void Cell_dsp(void);
      void View_dsp(void);
      void Clear_pr(void);
      void Top_proc(void);
      void Bot_proc(void);
      void Sum_proc(void);
      void Avg_proc(void);
      void Rng_proc(void);
      void Sqrt_pr(void);
      void Date_pr(void);
      void Mth_proc(void);
      void Day_proc(void);
      void Yr_proc(void);
      void Time_pr(void);
      void Hour_pr(void);
      void Min_proc(void);
      void Sec_proc(void);
      void Up_proc(void);
      void Down_pr(void);
      void Left_pr(void);
      void Right_pr(void);
      void Print_pr(void);
    double asc_2_dbl(void);
      void Pow_dsp(void);
 

    int main(int argc, char *argv[])
    {
       int opa, ops, opm, opd;
           
       char *sub;
      
       strcpy(sheet_nm, "*CELL");
       strcpy(wsp_name, "EMPTY");
      
       for(i = 0; i <= 98; i++)      
       {
          z1 = 1;
          for(j = 0; j <= 26; j++)
          {
             sheet[i][j][0] = '_';
             src[i][j][0] = '_';

             if((i == 0) && (j != 0))
             {
                if(z1 == 10)
                {
                   z1 = 17;
                }
                if(z1 == 26)
                {
                   z1 = 34;
                }
                
                sheet[i][j][0] = 'A'+z1-1;
                src[i][j][0] = 'A'+z1-1;
                z1++;
             }

             if((i != 0) && (j == 0))
             {
                sheet[i][j][0] = '0'+i;
                src[i][j][0] = '0'+i;
             }
             
             if((i == 0) && (j == 0))
             {
                sheet[i][j][0] = '\0';
                src[i][j][0] = '\0';
             }
          }
       }
       sheet[0][26][0] = 'Z';
       src[0][26][0] = 'Z';
       for(i = 1; i <= 98; i++)      
       {
          j = 26;
          {
             sheet[i][j][0] = '_';
             src[i][j][0] = '_';
          }
       }

       strcpy(sheet_nm, "EMPTY");
       strcpy(wsp_name, "EMPTY ");
       rct = 0;
       cct = 1;
       Cell_dsp();

       while(1)
       {

start1:
          printf("Enter the CMD or cell id: -> \n");
          scanf("%s",cellnum);

          cmd_byte = 0;
          if(strcmp(cellnum, "*EXIT") == 0)          cmd_byte=1;
          else if(strcmp(cellnum, "*CELL") == 0)     cmd_byte=2;
          else if(strcmp(cellnum, "*PROG") == 0)     cmd_byte=3;
          else if(strcmp(cellnum, "*FLAG") == 0)     cmd_byte=4;
          else if(strcmp(cellnum, "*MATH") == 0)     cmd_byte=5;
          else if(strcmp(cellnum, "*SAVE") == 0)     cmd_byte=6;
          else if(strcmp(cellnum, "*LOAD") == 0)     cmd_byte=7;
          else if(strcmp(cellnum, "*VIEW") == 0)     cmd_byte=8;
          else if(strcmp(cellnum, "*CLEAR") == 0)    cmd_byte=9;
          else if(strcmp(cellnum, "*HOME") == 0)     cmd_byte=10;
          else if(strcmp(cellnum, "*TOP") == 0)      cmd_byte=11;
          else if(strcmp(cellnum, "*BOT") == 0)      cmd_byte=12;
          else if(strcmp(cellnum, "*UP") == 0)       cmd_byte=13;
          else if(strcmp(cellnum, "*DOWN") == 0)     cmd_byte=14;
          else if(strcmp(cellnum, "*LEFT") == 0)     cmd_byte=15;
          else if(strcmp(cellnum, "*RIGHT") == 0)    cmd_byte=16;
          else if(strcmp(cellnum, "*PRINT") == 0)    cmd_byte=17;

          switch(cmd_byte)
          {   
             case 1:             /* *EXIT */
               return 0;
               break;

             case 2:             /* *CELL */
               goto skip_save; 
               break;

             case 3:             /* *PROG */
               Prog_dsp();
               goto start1;
               break;

             case 4:             /* *FLAG NO LONGER USED */
               break;            

             case 5:             /* *MATH */
               Math_dsp();
               goto start1;
               break;

             case 6:             /* *SAVE */
               printf("Saved Workspace Name --> \n");
               scanf("%s",wkspace);
               Save_wsp();
               strcpy(wsp_name, wkspace);
               goto skip_save;          
               break;

             case 7:             /* *LOAD */
               printf("Load Workspace Name --> \n");
               scanf("%s",wkspace);
               Load_wsp();
               strcpy(wsp_name, wkspace);
               goto skip_save;          
               break;

             case 8:             /* *VIEW */
               View_dsp();
               goto start1;
               break;

             case 9:             /* *CLEAR */
               Clear_pr();
               goto skip_save;           
               break;

             case 10:             /* *HOME */
               rct = 0;
               cct = 1;
               goto skip_save;
               break;

             case 11:             /* *TOP */
               Top_proc();
               goto skip_save;
               break;

             case 12:             /* *BOT */
               Bot_proc();
               goto skip_save;
               break;

             case 13:             /* *UP */
               Up_proc();
               goto skip_save;
               break;

             case 14:             /* *DOWN */
               Down_pr();
               goto skip_save;
               break;

             case 15:             /* *LEFT */
               Left_pr();
               goto skip_save;
               break;

             case 16:             /* *RIGHT */
               Right_pr();
               goto skip_save;
               break;

             case 17:             /* *PRINT */
               Print_pr();
               goto skip_save;
               break;

          }

          x = strlen(cellnum);

          if(x > 3)
          {
             printf("Input Error!\n");
             goto start1;
          }

          if(x == 2)
          {
             if((cellnum[0] >= 'A') && (cellnum[0] <= 'Z'))
                col = cellnum[0] - 'A'+1;
             else
                z2 = 0;
                for(z1 = 1; z1 <= 26; z1++)
                {
                   if(cellnum[0] == sheet[z2][z1][0])
                   {
                      col = z1;
                      break;
                   }
                }
              row = cellnum[1] - '1'+1;  /* now have row number */
          }

          if(x == 3)
          {
             if((cellnum[0] >= 'A') && (cellnum[0] <= 'Z'))
                col = cellnum[0] - 'A'+1;
             else
                z2 = 0;
                for(z1 = 1; z1 <= 26; z1++)
                {
                   if(cellnum[0] == sheet[z2][z1][0])
                   {
                      col = z1;
                      break;
                   }
                }

             wk_row[0] = cellnum[1];
             wk_row[1] = cellnum[2];
             wk_row[2] = '\0';
             row = atoi(wk_row);        /* now have row number */
          }

          if((row > 98) || (row < 0) || (col > 26) || (col < 0))
          {
             printf("\n Invalid cell number \n");
             continue; 
          }

	   opa = 0;
          ops = 0;
          opm = 0;
          opd = 0;

          printf("Enter the value to be inserted -> \n");
          gets(input);

          x = strlen(input);
          input[x-1] = '\0';
printf("input = %s\n",input);

          /*  load source (program) */
          strcpy(src[row][col], input);
                     
          p = strstr(input, "=");

          if(!p) 
          {
               p2 = strstr(input, "-");
               if(p2)
               {
                  p1 = strstr(input, ".");
                  if(p1)
                  {
                     value = atof(input);
                     spreadsheet[row][col] = value;
                     flag[row][col] = 1;
                     sprintf(sheet[row][col], "%.2f", value);
                  }
                  else
                  {
                     z4 = atoi(input);
                     sprintf(sheet[row][col], "%d", z4);
                     flag[row][col] = 1; 
                     spreadsheet[row][col] = z4;
                  }
               }
          }

          if(!p) 
          { 
             if(isNumber(input))        /*  numeric cell */
             {
                p1 = strstr(input, ".");
                if(p1)
                {
                   spreadsheet[row][col] = atof(input);
                }
                else
                {
                   spreadsheet[row][col] = atoi(input);
                }
                flag[row][col] = 1;
                strcpy(sheet[row][col],input);
                if(strlen(sheet[row][col]) > 12)
                {
                   sheet[row][col][12] = '\0';
                }
             }
             else                    /* text cell */     
             {
                strcpy(sheet[row][col], input);
                if(strlen(sheet[row][col]) > 19)
                {
                   sheet[row][col][19] = '\0';
                }
             }
        }

skip_save:

        /* *** Re-Compute *** */
       
        for(i9 = 1; i9 <= 98; i9++)
        {
           for(jj = 1; jj <= 26; jj++)  		/* i9 = row  jj = col */
           {
              proc_cel = 0;
              strcpy(input, src[i9][jj]);

              p = strstr(input, "_");
              if(!p)
              { 

              opa = 0;
              ops = 0;
              opm = 0;
              opd = 0;

              p = strstr(input, "+");
              if(p)
                 opa = 1;

              p = strstr(input, "-");
              if(p)
                 ops = 1;

              p = strstr(input, "*");
              if(p) 
                 opm = 1;

               p = strstr(input, "/");
               if(p)
                 opd = 1;

               if((opa == 1) || (ops == 1) || (opm == 1) || (opd == 1))
               {
                   pi = 0;
                   z3 = 1;
                   z4 = 1;
                   value = Expression();
                   sprintf(sheet[i9][jj],"%.2f",value);
                   proc_cel = 1;
               }

               p1 = strstr(input, "=");
               p2 = strstr(input, "-");

               if((!p1) && (p2))
               {
                  p1 = strstr(input, ".");
                  if(p1)
                  {
                     value = spreadsheet[i9][jj];
                     sprintf(sheet[i9][jj], "%.2f", value);
                  }
                  else
                  {
                     z4 = spreadsheet[i9][jj];
                     sprintf(sheet[i9][jj], "%d", z4);
                  }
               }
   
               pgm_byte = 0;
               p = strstr(input, "SUM");
               if(p)
                  pgm_byte = 1; 

               p = strstr(input, "AVG");
               if(p)
                  pgm_byte = 2; 

               p = strstr(input, "RNG");
               if(p)
                  pgm_byte = 3; 

               p = strstr(input, "DATE");
               if(p)
                  pgm_byte = 4; 

               p = strstr(input, "MTH");
               if(p)
                  pgm_byte = 5; 

               p = strstr(input, "DAY");
               if(p)
                  pgm_byte = 6; 

               p = strstr(input, "YR");
               if(p)
                  pgm_byte = 7; 

               p = strstr(input, "TIME");
               if(p)
                  pgm_byte = 8; 

               p = strstr(input, "HOUR");
               if(p)
                  pgm_byte = 9; 

               p = strstr(input, "MIN");
               if(p)
                  pgm_byte = 10; 

               p = strstr(input, "SEC");
               if(p)
                  pgm_byte = 11; 

               p = strstr(input, "SQRT");
               if(p)
                  pgm_byte = 12; 

               p = strstr(input, "POW");
               if(p)
                  pgm_byte = 13; 


               switch(pgm_byte)
               {   
                  case 1:             /* SUM */
                    Sum_proc();
                    break;

                  case 2:             /* AVG */
                    Avg_proc();
                    break;

                  case 3:             /* RNG */
                    Rng_proc();
                    break;

                  case 4:             /* DATE */
                    Date_pr();
                    break;

                  case 5:             /* MTH */
                    Mth_proc();
                    break;

                  case 6:             /* DAY */
                    Day_proc();
                    break;

                  case 7:             /* YR */
                    Yr_proc();
                    break;

                  case 8:             /* TIME */
                    Time_pr();
                    break;

                  case 9:             /* HOUR */
                    Hour_pr();
                    break;

                  case 10:             /* MIN */
                    Min_proc();
                    break;

                  case 11:             /* MIN */
                    Sec_proc();
                    break;

                  case 12:             /* SQRT */
                    Sqrt_pr();
                    break;

                  case 13:             /* POW  */
                    Pow_dsp();
                    break;

               }
             }
          }
        }
 
print_loop:
                  
        strcpy(sheet_nm, "*CELL");
        Cell_dsp();

     }               /* end of while(1) loop */
     return 0; 
}


int isNumber(char str[20])
{
   int i,j,k,flag = 1;
   for(i = 0; str[i] != '\0'; i++)
   {
      if((str[i] >= '0' && str[i] <= '9') || (str[i] == '.'))
      {}
      else
      {
         flag = 0;
         break;
      }
   }
   return flag;
}


double Expression()	
{
   char ch;
   
   double Value;

   z1 = 0;
   z4 = 0;
 
   ch = input[pi];
   if(ch != '=')
   {
      Value = 0;
      return;
   }

   while(ch != '=')
   {
      pi++;
      ch = input[pi];
   }
   pi++; 
   ch = input[pi];		/* got cell for math */
   varname[0] = ch;
   varname[1] = '\0';
   epos = pi;
   if(IsAddop(ch))
   {  
      Value = 0;  		
   }
   else
   {
     Value = Term();
     pi = epos;
     ch = input[pi];
   }

   while(IsAddop(ch))
   {
     switch(ch)
     {
        case '+':
          Match('+');
          Value = Value + Term();
          break;
    
        case '-':
          Match('-');
          Value = Value - Term();
          break;

        default:
          break;
     }
     pi = epos;
     ch = input[pi];
  }
  return Value;
}



double Term()		
{   
   char ch;
   int pi;
   double Value;

   Value = Factor();

   pi = epos;
   ch = input[pi];
   while(IsMultop(ch))
   {
     switch(ch)
     {
        case '*':
          Match('*');
          Value = Value * Factor();   
          break;
    
        case '/':
          Match('/');
          Value = Value / Factor();   
          break;

        case '^':
          Match('^');
          Value = pow(Value, Factor()); 
          break;

        case '%':
          Match('%');
          Value = (int) Value % (int) Factor();     
          break;

        default:
          break;
     }
     pi = epos;
     ch = input[pi];
  }
  return Value;
}



double Factor()                        
{ 
   char ch;
   int pi;
   double value;

   pi = epos; 
   ch = input[pi];

/* printf("\nFACTOR #1 ch = %c pi = %d input = %s\n",ch,pi,input); */

   if(ch == '(')
   {
     Match('(');
     value = Expression();
     Match(')');
   }
   else
   {
     if(isalpha(ch))			
     {
        z2 = 0;
        z1 = 0;
        ch = input[pi];
        x = strlen(input);

        for(z3 = z4; z3 <= x; z3++)
        {
           if(ch == ' ')
           {
              break;
           }
           if(ch == '+')
           {
              break;
           }
           if(ch == '-')
              break;
           if(ch == '*')
              break;
           if(ch == '/')
              break;
           if(ch == ' ')
              break;
           
           if(ch != '=')
           {
              wk_row[z2] = ch;
              z2++;
           }
           z1++;
           pi++;
           ch = input[pi];
        }
        wk_row[z2] = '\0';
/* printf("FACTOR #5 zi = %d 2 = %d z3 = %d ch = %c\n",pi,z2,z3,ch); */

        z3++;
        z3++;
        z4 = z3;

        x = strlen(wk_row);
        if(x == 2)
        {
             if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
             {
                z2 = 0;
                for(z1 = 1; z1 <= 26; z1++)
                {
                   if(wk_row[0] == sheet[z2][z1][0])
                   {
                      mcol = z1;
                      break;
                   }
                }
             }
               
             else
                z2 = 0;
                for(z1 = 1; z1 <= 26; z1++)
                {
                   if(wk_row[0] == sheet[z2][z1][0])
                   {
                      mcol = z1;
                      break;
                   }
                }
              mrow = wk_row[1] - '1'+1;  /* now have row number */
        }

        if(x == 3)
        {
             if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
             {
                z2 = 0;
                for(z1 = 1; z1 <= 26; z1++)
                {
                   if(wk_row[0] == sheet[z2][z1][0])
                   {
                      mcol = z1;
                      break;
                   }
                }
             }
             else
             
                z2 = 0;
                for(z1 = 1; z1 <= 26; z1++)
                {
                   if(wk_row[0] == sheet[z2][z1][0])
                   {
                      mcol = z1;
                      break;
                   }
                }
                wk_row1[0] = wk_row[1];
                wk_row1[1] = wk_row[2];
                wk_row1[2] = '\0';
                mrow = atoi(wk_row1);  
           }  

          value = spreadsheet[mrow][mcol];

          epos = pi;
     }
     else				
     {
         value = GetNum(); 
     }
  }
  return value;
}


double GetNum()			
{   
   char ch;
   int pi;
   double value=0;

   pi = epos;
   ch = input[pi];
   if((!isdigit(ch)) && (ch != '.'))
   {
     /*strcpy(t_holder, "Numeric Value"); */
     
   }
   value = asc_2_dbl();
/*
   pi = e_pos;
   ch = p_string[pi];
   if(isdigit(ch))
   {
     while(isdigit(ch))
     {
       pi++;
       ch = p_string[pi];
     }
     e_pos = pi;
  }
  SkipWhite();
*/
  return value;
}


double asc_2_dbl()
{   
   char ch, cvalue[33];
   int pi, vi_pos=0;
   double fvalue;

   pi = epos;
   ch = input[pi];
   while((isdigit(ch)) || (ch == '.') && (vi_pos <= 32))
   {
     cvalue[vi_pos] = ch;
     pi++;
     vi_pos++;
     ch = input[pi];
   }
   cvalue[vi_pos] = '\0';
   fvalue = atof(cvalue);                 
   epos = pi;
   return fvalue;
}


int IsAddop(char ch) 		
{   
   int rval=0;

   if((ch == '+') || (ch == '-'))
   {
     rval = 1;
   }
   return rval;
}



int IsMultop(char ch) 		
{   
   int rval=0;

   if(ch == '\0')
   {                       
     rval = 0;           
   }
   else if(strchr("*^/%", ch))
   {
     rval = 1;
   }
   return rval;
}



void Match(char x)             
{   
   char ch, string[6];
   int pi;

   pi = epos;
   ch = input[pi];
   if(ch != x)
   {
     strcpy(string, "\" \"");
     string[1] = x;
   }
   else
   {
     _GetChar();
     SkipWhite();
   }
}



void SkipWhite() 	
{   
   char ch;
   int pi;

   pi = epos;
   ch = input[pi];
   while(Is_White(ch))
   {
     _GetChar();
     pi = epos;
     ch = input[pi];
   }
}



void _GetChar()
{
  epos++;
}



int Is_White(char ch)
{   
   int test=0;

   if((ch == ' ') || (ch == '\t'))
   {
     test = -1;
   }
   return test;
}


void Save_wsp()
{
   int i,j,x,k9;

   char str1[17];
   char strc[3];
   char strr[3];
   char str[3];
   char tot_nm[5];

   strcpy(wk_file, wkspace);
   strcat(wk_file, " wps A");
   strcat(wk_file, "\0");
   fp = fopen(wk_file, "w");

   k9 = 0;
   for(i = 1; i < 99; i++)
   {
      for(j = 1; j < 26; j++)
      {
         p = strstr(src[i][j], "_");
         if(!p)
         {
           k9++;
         }
      }
   }

   sprintf(tot_nm, "%d", k9);
   fprintf(fp, "%s\n", tot_nm);

   /* source */
   for(i = 1; i < 99; i++)
   {
      for(j = 1; j < 26; j++)
      {
         p = strstr(src[i][j], "_");
         if(!p)
         {
            /*  get cell value */
            strcpy(str1, src[i][j]); 
 
           /* str[x-1] = '\0'; */
 
            /*  column value   */
            sprintf(strc, "%d", j);
  
            /*  row value  */
            sprintf(strr, "%d", i);
           
            switch(j)
            {
               case 1:
                 if(i < 10)
                 {
                    strcpy(str, " A");
                 }
                 else
                 {  
                    strcpy(str, "A");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 2:
                 if(i < 10)
                 {
                    strcpy(str, " B");
                 }
                 else
                 {  
                    strcpy(str, "B");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 3:
                 if(i < 10)
                 {
                    strcpy(str, " C");
                 }
                 else
                 {  
                    strcpy(str, "C");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 4:
                 if(i < 10)
                 {
                    strcpy(str, " D");
                 }
                 else
                 {  
                    strcpy(str, "D");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 5:
                 if(i < 10)
                 {
                    strcpy(str, " E");
                 }
                 else
                 {  
                    strcpy(str, "E");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 6:
                 if(i < 10)
                 {
                    strcpy(str, " F");
                 }
                 else
                 {  
                    strcpy(str, "F");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 7:
                 if(i < 10)
                 {
                    strcpy(str, " G");
                 }
                 else
                 {  
                    strcpy(str, "G");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 8:
                 if(i < 10)
                 {
                    strcpy(str, " H");
                 }
                 else
                 {  
                    strcpy(str, "H");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 9:
                 if(i < 10)
                 {
                    strcpy(str, " I");
                 }
                 else
                 {  
                    strcpy(str, "I");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 10:
                 if(i < 10)
                 {
                    strcpy(str, " J");
                 }
                 else
                 {  
                    strcpy(str, "J");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 11:
                 if(i < 10)
                 {
                    strcpy(str, " K");
                 }
                 else
                 {  
                    strcpy(str, "K");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 12:
                 if(i < 10)
                 {
                    strcpy(str, " L");
                 }
                 else
                 {  
                    strcpy(str, "L");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 13:
                 if(i < 10)
                 {
                    strcpy(str, " M");
                 }
                 else
                 {  
                    strcpy(str, "M");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 14:
                 if(i < 10)
                 {
                    strcpy(str, " N");
                 }
                 else
                 {  
                    strcpy(str, "N");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 15:
                 if(i < 10)
                 {
                    strcpy(str, " O");
                 }
                 else
                 {  
                    strcpy(str, "O");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 16:
                 if(i < 10)
                 {
                    strcpy(str, " P");
                 }
                 else
                 {  
                    strcpy(str, "P");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 17:
                 if(i < 10)
                 {
                    strcpy(str, " Q");
                 }
                 else
                 {  
                    strcpy(str, "Q");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 18:
                 if(i < 10)
                 {
                    strcpy(str, " R");
                 }
                 else
                 {  
                    strcpy(str, "R");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 19:
                 if(i < 10)
                 {
                    strcpy(str, " S");
                 }
                 else
                 {  
                    strcpy(str, "S");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 20:
                 if(i < 10)
                 {
                    strcpy(str, " T");
                 }
                 else
                 {  
                    strcpy(str, "T");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 21:
                 if(i < 10)
                 {
                    strcpy(str, " U");
                 }
                 else
                 {  
                    strcpy(str, "U");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 22:
                 if(i < 10)
                 {
                    strcpy(str, " V");
                 }
                 else
                 {  
                    strcpy(str, "V");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 23:
                 if(i < 10)
                 {
                    strcpy(str, " W");
                 }
                 else
                 {  
                    strcpy(str, "W");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 24:
                 if(i < 10)
                 {
                    strcpy(str, " X");
                 }
                 else
                 {  
                    strcpy(str, "X");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 25:
                 if(i < 10)
                 {
                    strcpy(str, " Y");
                 }
                 else
                 {  
                    strcpy(str, "Y");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;

               case 26:
                 if(i < 10)
                 {
                    strcpy(str, " Z");
                 }
                 else
                 {  
                    strcpy(str, "Z");
                 }
                 strcat(str, strr);
                 strcat(str, "\0");
                 break;
            }
            fprintf(fp, "%s %s\n", str,str1);
         }
      }     
   }
   fclose(fp);
}


void Load_wsp(void)
{
  int i,j,k,m;
  int lcol;
  int lrow;
  int tot_ct;
  int vv;

  char str[5];
  char str1[17];
  char w_str1[17];
  char wk_row[4];
  char *p1;
  char ch;
  char c;
  char wk_num[4];
 
  for(i = 0; i <= 98; i++)      
  {
      z1 = 1;
      for(j = 0; j <= 26; j++)
      {
         sheet[i][j][0] = '_';
         src[i][j][0] = '_';

         if((i == 0) && (j != 0))
         {
            if(z1 == 10)
            {
               z1 = 17;
            }
            if(z1 == 26)
            {
               z1 = 34;
            }
                
            sheet[i][j][0] = 'A'+z1-1;
            src[i][j][0] = 'A'+z1-1;
            z1++;
         }

         if((i != 0) && (j == 0))
         {
            sheet[i][j][0] = '0'+i;
            src[i][j][0] = '0'+i;
         }
             
         if((i == 0) && (j == 0))
         {
            sheet[i][j][0] = '\0';
            src[i][j][0] = '\0';
         }
      }
   }
   sheet[0][26][0] = 'Z';
   src[0][26][0] = 'Z';
   for(i = 1; i <= 98; i++)      
   {
       j = 26;
       {
          sheet[i][j][0] = '_';
          src[i][j][0] = '_';
       }
   }

   strcpy(wk_file, wkspace);
   strcat(wk_file, " wps A");
   strcat(wk_file, "\0");
   fp = fopen(wk_file, "r");
   if(fp == NULL)
   {
      printf("\nFile Not found = %s\n",wk_file);
      return;
   }
 
   printf("\n");
   /*  get record count */
   for(i = 0; i < 4; i++)
   {
      c = fgetc(fp);
      if(c == '\n')
      {
         break;
      }
      wk_num[i] = c;
   }
   wk_num[i] = '\0';
   tot_ct = atoi(wk_num); 
   
   /* source */
   tot_ct--;

   for(vv = 0; vv <= tot_ct; vv++)
   {
      for(k = 0; k < 4; k++)
      {
         c = fgetc(fp);
         if(c == '\n')
         {
            goto end1;
         }
         str[k] = c;
      }
end1:
      str[k] = '\0';

      x = strlen(str);

      x = 19;
      for(m = 0; m <= x; m++)
      { 
         c = fgetc(fp);
         if(c == '\n')
         {
            goto end2;
         }
         str1[m] = c;
      }
end2:
      str1[m] = '\0';
      x = strlen(str1);

      x = strlen(str);

      if(str[0] == ' ')
      {
         if((str[1] >= 'A') && (str[1] <= 'Z'))
            lcol = str[1] - 'A'+1;
            else
            lcol = str[1] - 'a'+1;     
            lrow = str[2] - '1'+1; 
      }
      else
      {
         if((str[0] >= 'A') && (str[0] <= 'Z'))
            lcol = str[0] - 'A'+1;
            else
            lcol = str[0] - 'a'+1;     
            wk_row[0] = str[1];
            wk_row[1] = str[2];
            wk_row[2] = '\0';
            lrow = atoi(wk_row);   
       }
     
       if(str1[0] == '-')
       {
           flag[lrow][lcol] = 1;
           p1 = strstr(str1, ".");
           if(p1)
           {
              spreadsheet[lrow][lcol] = atof(str1);
           }
           else
           {
              spreadsheet[lrow][lcol] = atoi(str1);
           }
       }

       if(isNumber(str1))     
       {
             p1 = strstr(str1, ".");
             if(p1)
             {
                spreadsheet[lrow][lcol] = atof(str1);
             }
             else
             {
                spreadsheet[lrow][lcol] = atoi(str1);
             }

             flag[lrow][lcol] = 1;
             strcpy(sheet[lrow][lcol], str1);
             strcpy(src[lrow][lcol], str1);
             if(strlen(sheet[lrow][lcol]) > 12)
             {
                sheet[lrow][lcol][12] = '\0';
                src[lrow][lcol][12] = '\0';
             }
          }
          else                    
          {
             strcpy(sheet[lrow][lcol], str1);
             strcpy(src[lrow][lcol], str1);
             if(strlen(sheet[lrow][lcol]) > 19)
             {
                sheet[lrow][lcol][19] = '\0';
                src[lrow][lcol][19] = '\0';
             }
          }
   }
   fclose(fp);
}


void Prog_dsp()
{
   int i, j;

   /* clr3270(); */
   printf("\n");  
 
   Get_date();
   Get_time();
 
   strcpy(sheet_nm, "*PROG");
   printf(" %s",f_date);
   printf("     Sheet Name -> %s",sheet_nm);
   printf("    Workspace Name -> %s",wsp_name);
   printf("       %s\n\n",f_time);

   i = 0;
   for(j = cct; j <= cct+4; j++)
   {
      printf("%18s",sheet[i][j]);
   }
   printf("\n\n");

   if(rct == 0)
   {
     rct = 1;
   }

   for(i = rct; i <= rct+15; i++)
   {
      if(i < 10)
        printf(" %d",i);
      if(i > 9)
        printf("%d",i);
        for(j = cct; j <= 4+cct; j++)
          printf("%18s",src[i][j]);
          printf("\n");
   }

   printf("\n Cmds:  *EXIT  *LOAD  *SAVE  *CLEAR  *PROG  *CELL  *MATH\n");
   printf("        *VIEW  *TOP   *BOT   *UP     *DOWN  *LEFT  *RIGHT \
           \n\n");
   strcpy(sheet_nm, "*PROG");
}


void Get_date()
{
    char tmp_var2[2];
    char tmp_var4[4];

    time_t T=time(NULL);
    struct  tm tm = *localtime(&T);
   
    day   = tm.tm_mday;            
    month = tm.tm_mon+1;       
    year  = tm.tm_year+1900; 
 
    sprintf(tmp_var2, "%d", month);
    strcpy(f_mth, tmp_var2);
    strcpy(f_date, tmp_var2);
    strcat(f_date, "/");
    sprintf(tmp_var2, "%d",day);
    strcat(f_date, tmp_var2);
    strcpy(f_day, tmp_var2);
    strcat(f_date, "/");
    sprintf(tmp_var4, "%d",year);
    strcat(f_date, tmp_var4);
    strcpy(f_yr, tmp_var4);
    strcat(f_date, "\0");  
}


void Get_time()
{
    char tmp_var2[2];
    char tmp_var4[4];

    time_t T=time(NULL);
    struct  tm tm = *localtime(&T);

    hour = tm.tm_hour;
    min = tm.tm_min;
    sec = tm.tm_sec;

    sprintf(tmp_var2, "%d", hour);
    strcpy(f_time, tmp_var2);
    strcat(f_time, ":");
    strcpy(f_hr, tmp_var2);
    sprintf(tmp_var2, "%d", min);
    strcat(f_time, tmp_var2);
    strcat(f_time , ":");
    strcpy(f_min, tmp_var2);
    sprintf(tmp_var2, "%d", sec);
    strcat(f_time, tmp_var2);
    strcat(f_time, "\0");
    strcpy(f_sec, tmp_var2);
}

void Math_dsp()
{
   clr3270();
   printf("\n");
  
   Get_date();
   Get_time();
 
   strcpy(sheet_nm, "*MATH");
   printf(" %s",f_date);
   printf("     Sheet Name -> %s",sheet_nm);
   printf("    Workspace Name -> %s",wsp_name);
   printf("       %s\n\n",f_time);

   i = 0;
   for(j = cct; j <= cct+4; j++)
   {
      printf("%19s",sheet[i][j]);
   }
   printf("\n\n");

   if(rct == 0)
   {
      rct = 1;
   }

   for(i = rct; i <= rct+15; i++)
   {
      if(i < 10)
        printf(" %d ",i);
      if(i > 9)
        printf("%d ",i);
      for(j = cct; j <= cct+4; j++)
      printf("%.2f   ",spreadsheet[i][j]);
      printf("\n");
   }

   printf("\n Cmds:  *EXIT  *PROG  *CELL\n");
   printf("        *VIEW  *TOP   *BOT   *UP  *DOWN  *LEFT  *RIGHT \
           \n\n");

}
 

void Cell_dsp()
{
        /* clr3270(); */ 
              
        Get_date();
        Get_time();

        printf(" %s",f_date);
        printf("     Sheet Name -> %s",sheet_nm);
        printf("    Workspace Name -> %s",wsp_name);
        printf("       %s\n\n",f_time);
     
        i = 0;
        for(j = cct; j <= cct+4; j++)
        {
            printf("%18s",sheet[i][j]);
        }
        printf("\n\n");

        if(rct == 0)
        {
           rct = 1;
        }

        for(i = rct; i <= rct+15; i++)
        {
           if(i < 10)
              printf(" %d",i);
           if(i > 9)
              printf("%d",i);
           for(j = cct; j <= 4+cct; j++)
              printf("%18s",sheet[i][j]);
              printf("\n");
        }
      
        printf("\n Cmds:  *EXIT  *LOAD  *SAVE");
        printf("  *HOME  *CLEAR  *PROG  *CELL  *MATH\n");
        printf("        *VIEW  *TOP   *BOT   *UP    *DOWN  *LEFT  *RIGHT \
               \n");

        return;
}


void View_dsp()
{
    clr3270();
    printf("\n");
               
    Get_date();
    Get_time();

    strcpy(sheet_nm, "*VIEW");
    printf(" %s",f_date);
    printf("     Sheet Name -> %s",sheet_nm);
    printf("    Workspace Name -> %s",wsp_name);
    printf("       %s\n\n",f_time);

err1:
    printf("Enter New Row (0 - 99) -> \n");
    scanf("%d",&rct);
    if((row < 0) || (row > 98))
    {
       printf("Invalid Row Number - Renter\n");
       goto err1;
    }

err2:
    printf("Enter New Col (A - Z) -> \n");
    scanf("%s",cellnum);

    z2 = 0;
    for(z1 = 1; z1 <= 26; z1++)
    {
       if(cellnum[0] == sheet[z2][z1][0])
       {
          cct = z1;
          break;
       }
    }

    if((cct < 1) || (cct > 26))
    {
       printf("ERROR Col MUST BE 1 or greater!\n");
       goto err2;
    }

    strcpy(sheet_nm, "*CELL");            
    Cell_dsp();
}


void Sum_proc()
{
   sum = 0;
   sub = strstr(input,"(");
   if(sub == NULL)
   {
      printf("SUM Input Error!\n");
   }
   else
   {
      z1 = 0;
      z4 = 0;
      z2 = 0;
      ch = input[z1];
      while(ch != '(')
      {
         z1++;
         ch = input[z1];
      }
      z1++;
      ch = input[z1];
      while(ch != ',')
      {
         wk_row[z2] = ch;
         z1++;
         z2++;
         ch = input[z1];
      }
      wk_row[z2] = '\0';

      x = strlen(wk_row);

      if(x == 2)
      {
         if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
         {      
                z2 = 0;
                z4 = 1;
                
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }
              i1 = wk_row[1] - '1'+1;  /* now have row number */

          }
      }

      if(x == 3)
      {
             ch = wk_row[0];

             if((ch >= 'A') && (ch <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(ch == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i1 = atoi(wk_row);        /* now have row number */
          }
      }


      z2 = 0;
      z1++;
      ch = input[z1];
      while(ch != ')')
      {
         wk_row[z2] = ch;
         z1++;
         z2++;
         ch = input[z1];
      }
      wk_row[z2] = '\0';

      x = strlen(wk_row);
      if(x == 2)
      {
         if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
         {      
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j2 = z4;
                      break;
                   }
                }
              i2 = wk_row[1] - '1'+1;  
          }
      }

      if(x == 3)
      {
             if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j2 = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i2 = atoi(wk_row);       
          }
      }


      if(i2 == i1)
      {
         for(j = j1; j <= j2; j++)
         {
            if(flag[i1][j] == 1)
            {
               sum += spreadsheet[i1][j];
               cnt++;
            }
         }
      }

      if(j2 == j1)
      {
         for(i = i1; i <= i2; i++)
         {
            if(flag[i][j1] == 1)
            {
               sum += spreadsheet[i][j1];
               cnt++;
            }
         }
      }

      sprintf(sheet[i9][jj],"%.2f",sum);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }
}


void Avg_proc(void)
{
   avg = 0;
   cnt = 0;
   sub = strstr(input,"(");
   if(sub == NULL)
   {
      printf("AVG Input Error!\n");
   }
   else 
   {
      z1 = 0;
      z2 = 0;
      z4 = 0;
      ch = input[z1];
      while(ch != '(')
      {
         z1++;
         ch = input[z1];
      }
      z1++;
      ch = input[z1];
      while(ch != ',')
      {
         wk_row[z2] = ch;
         z1++;
         z2++;
         ch = input[z1];
      }
      wk_row[z2] = '\0';

      x = strlen(wk_row);
      if(x == 2)
      {
         if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
         {      
                z2 = 0;
                z4 = 1;
                
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }
              i1 = wk_row[1] - '1'+1;  /* now have row number */

          }
      }

      if(x == 3)
      {
             ch = wk_row[0];

             if((ch >= 'A') && (ch <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(ch == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i1 = atoi(wk_row);        /* now have row number */
          }
      }

       z2 = 0;
       z1++;
       ch = input[z1];
       while(ch != ')')
       {
          wk_row[z2] = ch;
          z1++;
          z2++;
          ch = input[z1];
       }
       wk_row[z2] = '\0';

       x = strlen(wk_row);
      if(x == 2)
      {
         if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
         {      
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j2 = z4;
                      break;
                   }
                }
              i2 = wk_row[1] - '1'+1;  
          }
      }

      if(x == 3)
      {
             if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j2 = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i2 = atoi(wk_row);       
          }
      }

      if(i2 == i1)
       {
          for(j = j1; j <= j2; j++)
          {
             if(flag[i1][j] == 1)
             {
                avg += spreadsheet[i1][j];
                cnt++;
             }
          }
  	}

       if(j2 == j1)
       {
          for(i = i1; i <= i2; i++)
          {
             if(flag[i][j1] == 1)
             {
                avg += spreadsheet[i][j1];
                cnt++;
             }
          }
       }

       sprintf(sheet[i9][jj],"%.2f",avg/cnt);
       if(strlen(sheet[i9][jj]) > 12)
       {
          sheet[i9][jj][12] = '\0';
       }
    }
}



void Clear_pr()
{
  for(i = 0; i <= 98; i++)       
  {
     for(j = 0; j <= 25; j++)
     {
        sheet[i][j][0] = '_';
        src[i][j][0] = '_';
        sheet[i][j][1] = '\0';
        src[i][j][1] = '\0';
        flag[i][j] = 0;
        spreadsheet[i][j] = 0;

        z1 = 1;
        if((i == 0) && (j != 0))
        {
           if(z1 == 10)
           {
              z1 = 17;
           }
           if(z1 == 26)
           {
              z1 = 34;
           }
                
           sheet[i][j][0] = 'A'+z1-1;
           src[i][j][0] = 'A'+z1-1;
           z1++;
        }
     }
  }
  sheet[0][0][0] = '\0';
  src[0][0][0] = '\0';
}


void Rng_proc()
{
   sub = strstr(input,"(");
   if(sub == NULL)
   {
      printf("RNG Input Error!\n");
   }
   else 
   {
      z1 = 0;
      z2 = 0;
      z4 = 0;
      ch = input[z1];
      while(ch != '(')
      {
         z1++;
         ch = input[z1];
      }
      z1++;
      ch = input[z1];
      while(ch != ',')
      {
         wk_row[z2] = ch;
         z1++;
         z2++;
         ch = input[z1];
      }
      wk_row[z2] = '\0';

      x = strlen(wk_row);
      if(x == 2)
      {
         if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
         {      
                z2 = 0;
                z4 = 1;
                
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }
              i1 = wk_row[1] - '1'+1;  /* now have row number */

          }
      }

      if(x == 3)
      {
             ch = wk_row[0];

             if((ch >= 'A') && (ch <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(ch == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i1 = atoi(wk_row);        /* now have row number */
          }
      }

      z2 = 0;
      z1++;
      ch = input[z1];
      while(ch != ')')
      {
         wk_row[z2] = ch;
         z1++;
         z2++;
         ch = input[z1];
      }
      wk_row[z2] = '\0';

      x = strlen(wk_row);
      x = strlen(wk_row);
      if(x == 2)
      {
         if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
         {      
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j2 = z4;
                      break;
                   }
                }
              i2 = wk_row[1] - '1'+1;  
          }
      }

      if(x == 3)
      {
             if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j2 = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i2 = atoi(wk_row);       
          }
      }

      if(i1 == i2)
      {
         for(j = j1; j <= j2; j++)
         {
            if((flag[i1][j] == 1) && (maxm < spreadsheet[i1][j]))
            {
               maxm = spreadsheet[i1][j];
            }
            if((flag[i1][j] == 1) && (minm > spreadsheet[i1][j]))
            {
                minm = spreadsheet[i1][j];
            }
         }
      }

      if(j1 == j2)
      {
         for(i = i1; i <= i2; i++)
         {
            if((flag[i][j1] == 1) && (maxm < spreadsheet[i][j1]))
            {
               maxm = spreadsheet[i][j1];
            }
            if((flag[i][j1] == 1) && (minm > spreadsheet[i][j1]))
            {
                minm = spreadsheet[i][j1];
            }
         }
      }
      spreadsheet[row][col] = maxm-minm;
                     
      sprintf(sheet[i9][jj],"%.2f",avg/cnt);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }
}



void Date_pr()
{
   Get_date();

   strcpy(sheet[i9][jj], f_date);
   if(strlen(sheet[i9][jj]) > 17)
   {
      sheet[i9][jj][17] = '\0';
   }
}


void Mth_proc()
{
   Get_date();

   sprintf(input,"%d", month);
   if(isNumber(input))        /*  numeric cell */
   {
      p1 = strstr(input, ".");
      if(p1)
      {
         spreadsheet[i9][jj] = atof(input);
      }
      else
      {
         spreadsheet[i9][jj] = atoi(input);
      }
      flag[i9][jj] = 1;
      strcpy(sheet[i9][jj],input);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }                           
}


void Day_proc()
{
   Get_date();

   sprintf(input,"%d", day);
   if(isNumber(input))        /*  numeric cell */
   {
      p1 = strstr(input, ".");
      if(p1)
      {
         spreadsheet[i9][jj] = atof(input);
      }
      else
      {
         spreadsheet[i9][jj] = atoi(input);
      }
      flag[i9][jj] = 1;
      strcpy(sheet[i9][jj],input);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }                           
}


void Yr_proc()
{
   Get_date();

   sprintf(input,"%d", year);
   if(isNumber(input))        /*  numeric cell */
   {
      p1 = strstr(input, ".");
      if(p1)
      {
         spreadsheet[i9][jj] = atof(input);
      }
      else
      {
         spreadsheet[i9][jj] = atoi(input);
      }
      flag[i9][jj] = 1;
      strcpy(sheet[i9][jj],input);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }                           
}


void Time_pr()
{
   Get_time();

   strcpy(sheet[i9][jj], f_time);
   if(strlen(sheet[i9][jj]) > 17)
   {
      sheet[i9][jj][17] = '\0';
   }
}


void Hour_pr()
{
   Get_time();

   sprintf(input,"%d", hour);
   if(isNumber(input))        
   {
      p1 = strstr(input, ".");
      if(p1)
      {
         spreadsheet[i9][jj] = atof(input);
      }
      else
      {
         spreadsheet[i9][jj] = atoi(input);
      }
      flag[i9][jj] = 1;
      strcpy(sheet[i9][jj],input);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }                           
}


void Min_proc()
{
   Get_time();

   sprintf(input,"%d", min);
   if(isNumber(input))        
   {
      p1 = strstr(input, ".");
      if(p1)
      {
         spreadsheet[i9][jj] = atof(input);
      }
      else
      {
         spreadsheet[i9][jj] = atoi(input);
      }
      flag[i9][jj] = 1;
      strcpy(sheet[i9][jj],input);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }                           
}


void Sec_proc()
{
   Get_time();

   sprintf(input,"%d", sec);
   if(isNumber(input))        
   {
      p1 = strstr(input, ".");
      if(p1)
      {
         spreadsheet[i9][jj] = atof(input);
      }
      else
      {
         spreadsheet[i9][jj] = atoi(input);
      }
      flag[i9][jj] = 1;
      strcpy(sheet[i9][jj],input);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }                           
}


void Top_proc()
{
   rct = 0;
}


void Bot_proc()
{
   rct = 83;
}


void Sqrt_pr()
{
   sub = strstr(input,"(");
   if(sub == NULL)
   {
      printf("SQRT Input Error!\n");
   }
   else 
   {
      z1 = 0;
      z2 = 0;
      ch = input[z1];
      while(ch != '(')
      {
         z1++;
         ch = input[z1];
      }
      z1++;
      ch = input[z1];
      while(ch != ')')
      {
         wk_row[z2] = ch;
         z1++;
         z2++;
         ch = input[z1];
      }
      wk_row[z2] = '\0';

      x = strlen(wk_row);
      if(x == 2)
      {
         if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
         {      
                z2 = 0;
                z4 = 1;
                
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }
              i1 = wk_row[1] - '1'+1;  /* now have row number */

          }
      }

      if(x == 3)
      {
             ch = wk_row[0];

             if((ch >= 'A') && (ch <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(ch == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i1 = atoi(wk_row);        /* now have row number */
          }
      }

      value = spreadsheet[i1][j1];
      sum = sqrt(value);
      spreadsheet[i9][jj] = sum;
                     
      sprintf(sheet[i9][jj],"%.2f",sum);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }
}


void Up_proc()
{
    rct = rct - 15;
}


void Down_pr()
{
   rct = rct + 15;
}


void Left_pr()
{
   cct = cct - 4;
}


void Right_pr()
{
   cct = cct + 4;
}


void Print_pr()
{
   int st_row;
   int end_row;

   int st_col;
   int end_col;

   sum = 0;

   printf("Enter Starting Cell -> \n");
   scanf("%s",input);

   x = strlen(input);
   
/* printf("print_pr x = %d input = %s\n",x, input); */
   z1 = 0;
   z4 = 0;
   z2 = 0;
   
   if(x == 2)
   {
      wk_row[0] = input[0];
      wk_row[1] = input[1];
      wk_row[2] = '\0';
   }

   if(x == 3)
   {
      wk_row[0] = input[0];
      wk_row[1] = input[1];
      wk_row[2] = input[2];
      wk_row[3] = '\0';
   }

   x = strlen(wk_row);

/* printf("wk_row = %s x = %d\n",wk_row,x); */

   if(x == 2)
   {
      if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
      {      
         z2 = 0;
         z4 = 1;
                
         for(z4 = 1; z4 <= 26; z4++)
         {
            if(wk_row[0] == sheet[z2][z4][0])
            {
               j1 = z4;
               st_col = z4;
               break;
            }
         }
         i1 = wk_row[1] - '1'+1;  /* now have row number */
         st_row = i1;
      }
   }

   if(x == 3)
   {
             ch = wk_row[0];

             if((ch >= 'A') && (ch <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(ch == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      st_col = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i1 = atoi(wk_row);        /* now have row number */
             st_row = i1;
          }
      }
/* printf("st_col = %d st_row = %d\n",st_col,st_row); */

      printf("Enter Ending Cell -> \n");
      scanf("%s",input);

   z1 = 0;
   z4 = 0;
   z2 = 0;
   
   if(x == 2)
   {
      wk_row[0] = input[0];
      wk_row[1] = input[1];
      wk_row[2] = '\0';
   }

   if(x == 3)
   {
      wk_row[0] = input[0];
      wk_row[1] = input[1];
      wk_row[2] = input[2];
      wk_row[3] = '\0';
   }

   x = strlen(wk_row);

/* printf("wk_row = %s x = %d\n",wk_row,x); */

 
      x = strlen(wk_row);
      if(x == 2)
      {
         if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
         {      
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j2 = z4;
                      end_col = z4;
                      break;
                   }
                }
              i2 = wk_row[1] - '1'+1; 
              end_row = i2; 
          }
      }

      if(x == 3)
      {
             if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j2 = z4;
                      end_col = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i2 = atoi(wk_row);  
             end_row = i2;     
          }
      }
 

/* printf("end_col = %d end_row = %d\n",end_col, end_row); */

   fp = fopen("PRINTER", "w");

/*
   fprintf(fp, "%s","This is a test\n");
   fprintf(fp, "%s","LINE TWO\n");
  
   i = 0;
   for(j = cct; j <= cct+4; j++)
   {
      fprintf(fp,"%18s",sheet[i][j]);
   }
   fprintf(fp, "\n\n");

 fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);

*/

   fclose(fp);

/*
        i = 0;
        for(j = cct; j <= cct+4; j++)
        {
            printf("%18s",sheet[i][j]);
        }
        printf("\n\n");
*/

}


void Pow_dsp()
{
   double xx;

   z3 = 0;
   sub = strstr(input,"(");
   if(sub == NULL)
   {
      printf("POW Input Error!\n");
   }
   else 
   {
      z1 = 0;
      z2 = 0;
      ch = input[z1];
      while(ch != '(')
      {
         z1++;
         ch = input[z1];
      }
      z1++;
      ch = input[z1];
      while(ch != ',')
      {
         wk_row[z2] = ch;
         z1++;
         z2++;
         ch = input[z1];
      }
      wk_row[z2] = '\0';
      z3 = z1;

      x = strlen(wk_row);
      if(x == 2)
      {
         if((wk_row[0] >= 'A') && (wk_row[0] <= 'Z'))
         {      
                z2 = 0;
                z4 = 1;
                
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(wk_row[0] == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }
              i1 = wk_row[1] - '1'+1;  /* now have row number */
          }
      }

      if(x == 3)
      {
             ch = wk_row[0];

             if((ch >= 'A') && (ch <= 'Z'))
             {
                z2 = 0;
                z4 = 1;
                for(z4 = 1; z4 <= 26; z4++)
                {
                   if(ch == sheet[z2][z4][0])
                   {
                      j1 = z4;
                      break;
                   }
                }

             wk_row[0] = wk_row[1];
             wk_row[1] = wk_row[2];
             wk_row[2] = '\0';
             i1 = atoi(wk_row);        /* now have row number */
          }
      }
      value = spreadsheet[i1][j1];

      z2 = 0;
      z1++;
      ch = input[z1];
      while(ch != ')')
      {
         wk_row[z2] = ch;
         z1++;
	  z2++;
         ch = input[z1];
      }
      wk_row[z2] = '\0';
      xx = atof(wk_row);

      sum = pow(value,xx);
      spreadsheet[i9][jj] = sum;
                     
      sprintf(sheet[i9][jj],"%.2f",sum);
      if(strlen(sheet[i9][jj]) > 12)
      {
         sheet[i9][jj][12] = '\0';
      }
   }
}
