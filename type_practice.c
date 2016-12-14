
void type_practice(){
        int i=0,j=0,miss=0,percent=0,total=0;
        char c[2]=" ";
        char missc[4],accc[4];
        int space = 3;
        int end = 10;

        // 오타 검사하는 배열
        int pi[11][100];

		// 타자 연습 예문
		char pr[11][100] = {
			"The difficulty in life is the choice.",
			"Give me liberty or give me death.",
			"Example is better than precept.",
			"Friend in need is friend indeed.",
			"The family is one of nature's masterpieces.",
			"Our ideals are our better selves.",
			"Power is dangerous unless you have humility.",
			"Books cannot never teach the use of books.",
			"Slow and steady win the game.",
			"Patience is the key to paradise."}; //가독하기 쉽게 행별로 줄 나눔

        //setting
        clear();
	
	//ui 구성
	move(0, 0);
	addstr("------------------------------------------------------------");
	move(2, 0);
	addstr("------------------------------------------------------------");

        for(j=0 ; j<10 ; j++){
                move(j * 3 + space ,space); //move 내에서는 무조건 j에는 *3을 붙이기 바람
                addstr(pr[j]); //행렬 내부에선 j만 적음
		move(j * 3 + space + 2, 0);
		addstr("------------------------------------------------------------");
        }

        //오타율 출력
        move(1,space);
        addstr("miss    0 |  accuracy    0%");

        move(4,space);
        refresh();
        j=0;
        i=space;

        //짜다보니 j는 행렬이 기준이고 i는 커서 기준이 되어버렸습니다.
        //헷갈리지 않도록 주의 바랍니다.

        //start
        while(1) {
                c[0] = getchar();
                if( c[0] == 127 && i == space){}
                else{
                        if( c[0]==127 && i != space ){
                                move( j*3+space , i-1 );
                                addch( pr[ j ][ i - 1 - space] );
                                move( (j * 3) + space + 1 , i - 1);
                                addch(' ');
                                if(pi[j][i-1-space] == 1){
                                        miss--;
                                }
                                total--;

                                i= i-2;
                        }

						//틀렸을 경우
                        else if( c[0] != pr[j][i-space] ) {
                                move(j*3+space,i);
								//터미널색과 글자색 변경
                                attron(COLOR_PAIR(1));
                                addch(pr[j][i-space]);
								//터미널색과 글자색 복구
                                attroff(COLOR_PAIR(1));
                                move((j*3)+space+1,i);
                                addch(c[0]);
                                pi[j][i-space] = 1;
                                refresh();
                                total++;
                                miss++;
                        }

						//맞을 경우
                        else {
                                addch(c[0]);
                                pi[j][i-space] = 0;
                                refresh();
                                total++;
                        }

                        //오타율
                        move(1,9);
                        if(miss<1000){
                                if(miss >=100){
                                        missc[0] = miss/100 + '0';
                                }
                                else {
                                        missc[0] = ' ';
                                }
                                if(miss>=10){
                                        missc[1] = (miss/10)%10 + '0';
                                }
                                else{
                                        missc[1] = ' ';
                                }
                                missc[2] = miss%10 + '0';
                                missc[3] = '\0';
                                addstr(missc);
                        }
                        else{
                                move(1,8);
                                addstr("999+");
                        }


                        //정확도
                        move(1,26);
                        if(total != 0){
                                percent = (total - miss)*100/total;
                        }
                        else
                                percent = 0;
                        if(percent >=100){
                                accc[0] = percent/100 + '0';
                        }
                        else {
                                accc[0] = ' ';
                        }
                        if(percent >=10){
                                accc[1] = (percent/10)%10 + '0';
                        }
                        else {
                                accc[1] = ' ';
                        }
                        accc[2] = percent%10 + '0';
                        accc[3] = '\0';
                        addstr(accc);

                        i++; //커서 한 칸 옆으로
                        move((j*3)+space+1,i);

                        //문장의 끝에서 다음 줄로
                        if(pr[j][i-space] == '\0'){
                                i = space; //space는 앞의 여백임
                                j++; //j는 배열 기준이라서 1만 증가
                                move((j*3)+space+1,i); //j*3은 화면 기준이라 *3을 추가
                        }

                        refresh(); //화면 표시

                        if(j == end){
                                c[0] = getchar();
                                break;
                        }
                }
        }
}
