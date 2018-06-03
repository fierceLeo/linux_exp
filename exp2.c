    /*  
    鎿嶄綔绯荤粺瀹為獙涔嬫椂闂寸墖杞浆绠楁硶鍜屼紭鍏堢骇璋冨害绠楁硶  
    By Visual C++ 6.0  
    */   
    #include <stdio.h>   
    #include <stdlib.h>   
    #include <string.h>   
    typedef struct node   
    {   
      char name[20];    /*杩涚▼鐨勫悕瀛?/   
      int prio;     /*杩涚▼鐨勪紭鍏堢骇*/   
      int round;     /*鍒嗛厤CPU鐨勬椂闂寸墖*/   
      int cputime;    /*CPU鎵ц鏃堕棿*/   
      int needtime;    /*杩涚▼鎵ц鎵€闇€瑕佺殑鏃堕棿*/   
      char state;     /*杩涚▼鐨勭姸鎬侊紝W鈥斺€斿氨缁€侊紝R鈥斺€旀墽琛屾€侊紝F鈥斺€斿畬鎴愭€?/   
      int count;     /*璁板綍鎵ц鐨勬鏁?/   
      struct node *next;   /*閾捐〃鎸囬拡*/   
    }PCB;   
    PCB *ready=NULL,*run=NULL,*finish=NULL; /*瀹氫箟涓変釜闃熷垪锛屽氨缁槦鍒楋紝鎵ц闃熷垪鍜屽畬鎴愰槦鍒?/   
    int num;   
    void GetFirst();    /*浠庡氨缁槦鍒楀彇寰楃涓€涓妭鐐?/   
    void Output();     /*杈撳嚭闃熷垪淇℃伅*/   
    void InsertPrio(PCB *in);  /*鍒涘缓浼樺厛绾ч槦鍒楋紝瑙勫畾浼樺厛鏁拌秺灏忥紝浼樺厛绾ц秺楂?/   
    void InsertTime(PCB *in);  /*鏃堕棿鐗囬槦鍒?/   
    void InsertFinish(PCB *in);  /*鏃堕棿鐗囬槦鍒?/   
    void PrioCreate();    /*浼樺厛绾ц緭鍏ュ嚱鏁?/   
    void TimeCreate();    /*鏃堕棿鐗囪緭鍏ュ嚱鏁?/   
    void Priority();    /*鎸夌収浼樺厛绾ц皟搴?/   
    void RoundRun();    /*鏃堕棿鐗囪疆杞皟搴?/   
    int main(void)   
    {   
      char chose;   
      printf("璇疯緭鍏ヨ鍒涘缓鐨勮繘绋嬫暟鐩?\n");   
      scanf("%d",&num);   
      getchar();   
      printf("杈撳叆杩涚▼鐨勮皟搴︽柟娉曪細(P/R)\n");   
      scanf("%c",&chose);   
      switch(chose)   
      {   
      case 'P':   
      case 'p':   
        PrioCreate();   
        Priority();       
        break;   
      case 'R':   
      case 'r':   
        TimeCreate();   
        RoundRun();   
        break;   
      default:break;   
      }   
      Output();   
      return 0;   
    }   
    void GetFirst()  /*鍙栧緱绗竴涓氨缁槦鍒楄妭鐐?/   
    {   
      run = ready;   
         
      if(ready!=NULL)   
      {   
        run ->state = 'R';   
        ready = ready ->next;   
        run ->next = NULL;   
      }   
    }   
    void Output()    /*杈撳嚭闃熷垪淇℃伅*/   
    {   
      PCB *p;   
      p = ready;   
      printf("杩涚▼鍚峔t浼樺厛绾t杞暟\tcpu鏃堕棿\t闇€瑕佹椂闂碶t杩涚▼鐘舵€乗t璁℃暟鍣╘n");   
      while(p!=NULL)   
      {   
        printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);   
        p = p->next;   
      }   
      p = finish;   
      while(p!=NULL)   
      {   
        printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);   
        p = p->next;   
      }   
      p = run;   
      while(p!=NULL)   
      {   
        printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);   
        p = p->next;   
      }   
    }   
    void InsertPrio(PCB *in) /*鍒涘缓浼樺厛绾ч槦鍒楋紝瑙勫畾浼樺厛鏁拌秺灏忥紝浼樺厛绾ц秺浣?/   
    {   
      PCB *fst,*nxt;   
      fst = nxt = ready;   
         
      if(ready == NULL)  /*濡傛灉闃熷垪涓虹┖锛屽垯涓虹涓€涓厓绱?/   
      {   
        in->next = ready;   
        ready = in;   
      }   
      else     /*鏌ュ埌鍚堥€傜殑浣嶇疆杩涜鎻掑叆*/   
      {   
        if(in ->prio >= fst ->prio)  /*姣旂涓€涓繕瑕佸ぇ锛屽垯鎻掑叆鍒伴槦澶?/   
        {   
          in->next = ready;   
          ready = in;   
        }   
        else   
        {   
          while(fst->next != NULL)  /*绉诲姩鎸囬拡鏌ユ壘绗竴涓埆瀹冨皬鐨勫厓绱犵殑浣嶇疆杩涜鎻掑叆*/   
          {   
            nxt = fst;   
            fst = fst->next;   
          }   
             
          if(fst ->next == NULL) /*宸茬粡鎼滅储鍒伴槦灏撅紝鍒欏叾浼樺厛绾ф暟鏈€灏忥紝灏嗗叾鎻掑叆鍒伴槦灏惧嵆鍙?/   
          {   
            in ->next = fst ->next;   
            fst ->next = in;   
          }   
          else     /*鎻掑叆鍒伴槦鍒椾腑*/   
          {   
            nxt = in;   
            in ->next = fst;   
          }   
        }   
      }   
    }   
    void InsertTime(PCB *in)  /*灏嗚繘绋嬫彃鍏ュ埌灏辩华闃熷垪灏鹃儴*/   
    {   
      PCB *fst;   
      fst = ready;   
         
      if(ready == NULL)   
      {   
        in->next = ready;   
        ready = in;   
      }   
      else   
      {   
        while(fst->next != NULL)   
        {   
          fst = fst->next;   
        }   
        in ->next = fst ->next;   
        fst ->next = in;   
      }   
    }   
    void InsertFinish(PCB *in)  /*灏嗚繘绋嬫彃鍏ュ埌瀹屾垚闃熷垪灏鹃儴*/   
    {   
      PCB *fst;   
      fst = finish;   
         
      if(finish == NULL)   
      {   
        in->next = finish;   
        finish = in;   
      }   
      else   
      {   
        while(fst->next != NULL)   
        {   
          fst = fst->next;   
        }   
        in ->next = fst ->next;   
        fst ->next = in;   
      }   
    }   
    void PrioCreate() /*浼樺厛绾ц皟搴﹁緭鍏ュ嚱鏁?/   
    {   
      PCB *tmp;   
      int i;   
         
      printf("杈撳叆杩涚▼鍚嶅瓧鍜岃繘绋嬫墍闇€鏃堕棿锛歕n");   
      for(i = 0;i < num; i++)   
      {   
        if((tmp = (PCB *)malloc(sizeof(PCB)))==NULL)   
        {   
          perror("malloc");   
          exit(1);   
        }   
        scanf("%s",tmp->name);   
        getchar();    /*鍚告敹鍥炶溅绗﹀彿*/   
        scanf("%d",&(tmp->needtime));   
        tmp ->cputime = 0;   
        tmp ->state ='W';   
        tmp ->prio = 50 - tmp->needtime;  /*璁剧疆鍏朵紭鍏堢骇锛岄渶瑕佺殑鏃堕棿瓒婂锛屼紭鍏堢骇瓒婁綆*/   
        tmp ->round = 0;   
        tmp ->count = 0;   
        InsertPrio(tmp);      /*鎸夌収浼樺厛绾т粠楂樺埌浣庯紝鎻掑叆鍒板氨缁槦鍒?/   
      }   
    }   
    void TimeCreate() /*鏃堕棿鐗囪緭鍏ュ嚱鏁?/   
    {   
      PCB *tmp;   
      int i;   
         
      printf("杈撳叆杩涚▼鍚嶅瓧鍜岃繘绋嬫椂闂寸墖鎵€闇€鏃堕棿锛歕n");   
      for(i = 0;i < num; i++)   
      {   
        if((tmp = (PCB *)malloc(sizeof(PCB)))==NULL)   
        {   
          perror("malloc");   
          exit(1);   
        }   
        scanf("%s",tmp->name);   
        getchar();   
        scanf("%d",&(tmp->needtime));   
        tmp ->cputime = 0;   
        tmp ->state ='W';   
        tmp ->prio = 0;   
        tmp ->round = 2;  /*鍋囪姣忎釜杩涚▼鎵€鍒嗛厤鐨勬椂闂寸墖鏄?*/   
        tmp ->count = 0;   
        InsertTime(tmp);   
      }   
    }   
    void Priority()   /*鎸夌収浼樺厛绾ц皟搴︼紝姣忔鎵ц涓€涓椂闂寸墖*/   
    {   
      int flag = 1;   
         
      GetFirst();   
      while(run != NULL)  /*褰撳氨缁槦鍒椾笉涓虹┖鏃讹紝鍒欒皟搴﹁繘绋嬪鎵ц闃熷垪鎵ц*/   
      {   
        Output();  /*杈撳嚭姣忔璋冨害杩囩▼涓悇涓妭鐐圭殑鐘舵€?/   
        while(flag)   
        {   
          run->prio -= 3; /*浼樺厛绾у噺鍘讳笁*/   
          run->cputime++; /*CPU鏃堕棿鐗囧姞涓€*/   
          run->needtime--;/*杩涚▼鎵ц瀹屾垚鐨勫墿浣欐椂闂村噺涓€*/   
          if(run->needtime == 0)/*濡傛灉杩涚▼鎵ц瀹屾瘯锛屽皢杩涚▼鐘舵€佺疆涓篎锛屽皢鍏舵彃鍏ュ埌瀹屾垚闃熷垪*/   
          {   
            run ->state = 'F';   
            run->count++; /*杩涚▼鎵ц鐨勬鏁板姞涓€*/   
            InsertFinish(run);   
            flag = 0;   
          }   
          else   /*灏嗚繘绋嬬姸鎬佺疆涓篧锛屽叆灏辩华闃熷垪*/   
          {   
            run->state = 'W';   
            run->count++; /*杩涚▼鎵ц鐨勬鏁板姞涓€*/   
            InsertTime(run);   
            flag = 0;   
          }   
        }   
        flag = 1;   
        GetFirst();    /*缁х画鍙栧氨缁槦鍒楅槦澶磋繘绋嬭繘鍏ユ墽琛岄槦鍒?/   
      }   
    }   
    void RoundRun()    /*鏃堕棿鐗囪疆杞皟搴︾畻娉?/   
    {   
         
      int flag = 1;   
         
      GetFirst();   
      while(run != NULL)   
      {   
        Output();   
        while(flag)   
        {   
          run->count++;   
          run->cputime++;   
          run->needtime--;   
          if(run->needtime == 0) /*杩涚▼鎵ц瀹屾瘯*/   
          {   
            run ->state = 'F';   
            InsertFinish(run);   
            flag = 0;   
          }   
          else if(run->count == run->round)/*鏃堕棿鐗囩敤瀹?/   
          {   
            run->state = 'W';   
            run->count = 0;   /*璁℃暟鍣ㄦ竻闆讹紝涓轰笅娆″仛鍑嗗*/   
            InsertTime(run);   
            flag = 0;   
          }   
        }   
        flag = 1;   
        GetFirst();   
      }   
    }   
