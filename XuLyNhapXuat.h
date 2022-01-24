string convertToString(char* a)
{
    int i;
    string s = "";
    for (i = 0; a[i] != '\0'; i++) {
        s = s + a[i];
    }
    return s;
}
void NhapMa(char *mang, short soLuongKyTu, bool kieuDuLieu, short x, short y){
	// chucNang = 1: Nhap ma, chucNang = 2: Sua ma, chucNang = 3: Nhap ma de tim kiem
	// kieuDulieu = 0: So, kieuDuLieu = 1: Chu va so
	setbkcolor(15);
	setcolor(0);
	char tam;
    short i = strlen(mang);
	mang[i] = '|'; mang[i+1] = '\0';

    while (1){
		delay(10);
		outtextxy(x + 10,y + 7, mang);
		if (kbhit()){
			tam = getch();
			tam = toupper(tam);
			if (tam == BACKSPACE && i > 0){
					mang[i - 1] = '|';
					mang[i] = '\0';
					i--;
					xoa_input(x,y);
			}
			else if (tam == ESC){
				mang[0] = '\0';
				return;
			}
			else if (tam == ENTER)
			{
				if (i == 0){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.", "THONG BAO", MB_OK);
				} 
				else{
					mang[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, mang);
					break;
				}
			} 
			else if (i == soLuongKyTu - 2) continue;
			else if (kieuDuLieu == 0 && (tam >= '0' && tam <= '9')){
				mang[i] = tam;
				i++;
				mang[i] = '|';
				mang[i + 1] = '\0';
			}
			else if (kieuDuLieu == 1 && ((tam >= '0' && tam <= '9') || (tam >= 'A' && tam <= 'Z'))){
					mang[i] = tam;
					i++;
					mang[i] = '|';
					mang[i + 1] = '\0';
			}
			else continue;
		}
    }
}
void NhapNienKhoa(unsigned short &so, short x, short y){
	setbkcolor(15);
	setcolor(0);

	char a[6];
	char tam;
	short i = 0;

	if (so == 0){
		a[0] = '|'; a[1] = '\0';
	}
	else{
		itoa(so,a,10);
		i = strlen(a);
		a[i] = '|'; a[i + 1] = '\0';
	}
	
    while (1){
    	delay(10);
		outtextxy(x + 10, y + 7, a);
		if (kbhit()){
    		tam = getch();
	        if (tam == BACKSPACE && i > 0)
			{
				a[i - 1] = '|';
				a[i] = '\0';
				i--;
				xoa_input(x,y);
			}
	        else if (tam == ENTER)
			{
				if (i < 4){ 
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"NIEN KHOA PHAI CO 4 SO. VI DU: 2020.", "THONG BAO", MB_OK);
				}
				else{
					a[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, a);
					break;
				}
			}
			else if (tam == ESC){
				so = 0;
				return;
			}
	        else if (i == 4) continue;
	        else if (tam >= '0' && tam <= '9'){
	            a[i] = tam;
				i++;
				a[i] = '|';
				a[i + 1] = '\0';
	        }
	        else continue;
		}
    }

    so = atoi(a);

	while (so <= 2000){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"NIEN KHOA PHAI LON HON 2000.", "THONG BAO", MB_OK);
		xoa_input(x,y);
		NhapNienKhoa(so,x,y);
	}
}
void NhapHocKy(unsigned short &so, short x, short y){
	setbkcolor(15);
	setcolor(0);

	char a[3];
	char tam;

	if (so == 0){
		a[0] = '|'; a[1] = '\0';
	}
	else{
		a[0] = so + 48;
		a[1] = '|';
		a[2] = '\0';
	}
	
    while (1){
		delay(10);
		outtextxy(x + 10, y + 7, a);
    	if (kbhit()){
    		tam = getch();
	        if (tam == BACKSPACE && a[0] != '|')
			{
				a[0] = '|';
				a[1] = '\0';
				xoa_input(x,y);
			}
	        else if (tam == ENTER)
			{
				if (a[0] == '|'){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.", "THONG BAO", MB_OK);
				}
				else{
					a[1] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, a);
					break;
				}
			}
			else if (tam == ESC){
				so = 0;
				return;
			}
	        else if (a[0] >= '1' && a[0] <= '3') continue;
	        else if (tam >= '1' && tam <= '3'){
				a[0] = tam;
	            a[1] = '|';
				a[2] = '\0';
	        }
	        else continue;
		}
    }

    so = a[0] - 48;
}
void NhapNhom(unsigned short &so, short x, short y){
	setbkcolor(15);
	setcolor(0);

	char a[3];
	char tam;
	short i = 0;

	if (so == 0){
		a[0] = '|'; a[1] = '\0';
	}
	else{
		itoa(so,a,10);
		i = strlen(a);
		a[i] = '|'; a[i + 1] = '\0';
	}
	
    while (1){
		delay(10);
    	outtextxy(x + 10, y + 7, a);
		if (kbhit()){
    		tam = getch();
	        if (tam == BACKSPACE && i > 0)
			{
				a[i - 1] = '|';
				a[i] = '\0';
				i--;
				xoa_input(x,y);
			}
	        else if (tam == ENTER)
			{
				if (i == 0){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.", "THONG BAO", MB_OK);
				}
				else{
					a[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, a);
					break;
				}
			}
			else if (tam == ESC){
				so = 0;
				return;
			}
	        else if (i == 1) continue;
	        else if (tam >= '1' && tam <= '9'){
	            a[i] = tam;
				i++;
				a[i] = '|';
				a[i + 1] = '\0';
	        }
	        else continue;
		}
    }

    so = atoi(a);
}
void NhapSoLuongSV(unsigned short &so, short x, short y){
	setbkcolor(15);
	setcolor(0);
	char a[6];
	char tam;
	short i = 0;

	if (so == 0){
		a[0] = '|'; a[1] = '\0';
	}
	else{
		itoa(so,a,10);
		i = strlen(a);
		a[i] = '|'; a[i + 1] = '\0';
	}
	
    while (1){
    	delay(10);
		outtextxy(x + 10, y + 7, a);
		if (kbhit()){
    		tam = getch();
	        if (tam == BACKSPACE && i > 0)
			{
				a[i - 1] = '|';
				a[i] = '\0';
				i--;
				xoa_input(x,y);
			}
	        else if (tam == ENTER)
			{
				if (i == 0){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.", "THONG BAO", MB_OK);
				}
				else{
					a[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, a);
					break;
				}
			}
			else if (tam == ESC){
				so = 0;
				return;
			}
	        else if (i == 3) continue;
	        else if (tam >= '0' && tam <= '9'){
	            a[i] = tam;
				i++;
				a[i] = '|';
				a[i + 1] = '\0';
	        }
	        else continue;
		}
    }
    
	so = atoi(a);
	
	while (so == 0){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"SO LUONG SINH VIEN PHAI KHAC 0.", "THONG BAO", MB_OK);
		xoa_input(x,y);
		NhapSoLuongSV(so,x,y);
	}
}
short NhapDiem(float &diem, short chon, short sl, short x, short y){
	char tam[10];
	char kytu;
	short i = 0;

	if (diem == -1){
		tam[0] = '|';
		tam[1] = '\0';
	}
	else{
		ftoa(diem,tam);
		i = strlen(tam);
		tam[i] = '|';
		tam[i+1] = '\0';
	}

	while (1){
		delay(10);
		outtextxy(x+5,y+12,tam);
		if (kbhit()){
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu){
				case KEY_UP:
					if (chon > 0){
						if (i == 0){
							XoaDiem(y);
							diem = -1;
							return 1;
						}
						tam[i] = '\0';
						diem = atof(tam);
						XoaDiem(y);
						outtextxy(x+5,y+12,tam);
						return 1;
					}
					break;
				case KEY_DOWN:
				case ENTER:
					if (chon + 1 < sl){
						if (i == 0){
							XoaDiem(y);
							diem = -1;
							return 2;
						}
						tam[i] = '\0';
						diem = atof(tam);
						XoaDiem(y);
						outtextxy(x+5,y+12,tam);
						return 2;
					}
					break;
				case ESC:
					if (i == 0){
						diem = -1;
						return 0;
					}
					tam[i] = '\0';
					diem = atof(tam);
					return 0;
				case BACKSPACE:
					if (i > 0){
						tam[i-1] = '|';
						tam[i] = '\0';
						i--;
						XoaDiem(y);
					}
					break;
				default:{
					if (i == 3) continue;
					else if (i == 0 && (kytu >= '0' && kytu <= '9')){
						tam[i++] = kytu;
						tam[i] = '|';
						tam[i+1] = '\0';
					}
					else if (i == 1 && ((tam[0] == '1' && kytu == '0') || kytu == '.')){
						tam[i++] = kytu;
						tam[i] = '|';
						tam[i+1] = '\0';
					}
					else if (i == 2){
						if (tam[0] == '1' && tam[1] == '0') continue;
						else if (kytu >= '0' && kytu <= '9'){
							tam[i++] = kytu;
							tam[i] = '|';
							tam[i+1] = '\0';
						}
					}
				}
			}
		}
	}
}

void Nhap_Ho_SV(char *ma, unsigned short soLuongKyTu, short x, short y)
{
    setbkcolor(15);
	setcolor(0);
    char tam;
    unsigned short i = strlen(ma);
    ma[i] = '|';
    ma[i+1] = '\0';
    while(1)
    {
        delay(10);
        outtextxy(x + 10, y + 7, ma);
        if (kbhit())
        {
            tam = getch();
            tam = toupper(tam);
            if (tam == BACKSPACE && i > 0){
                ma[i - 1] = '|';
                ma[i] = '\0';
                i--;
                xoa_input(x,y);
            }
            else if (tam == ESC){
				ma[0] = '\0';
				return;
			}
            else if (tam == ENTER)
			{
				if (i == 0){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.", "THONG BAO", MB_OK);
				}
				else{
					ma[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, ma);
					break;
				}
			} 
            else if ((tam == ' ' && i == 0) || (tam == ' ' && ma[i - 1] == ' ')) // bỏ khoảng trắng giữa và đầu
                continue;
            else if (tam >= 'A' && tam <= 'Z')
            {
                if (i == soLuongKyTu - 2) continue;
                ma[i] = tam;
                i++;
                ma[i] = '|';
                ma[i+1] = '\0';
            }
            else if (tam == 32) // Nhận 1 khoảng trắng
            {
                ma[i] = tam;
                i++;
                ma[i] = '|';
                ma[i+1] = '\0';
            }
            else continue; // bỏ qua số và các kí tự khác
        }
    }
    if(ma[i-1]==' ')
        ma[i-1]=ma[i];
}

void Nhap_Ten_SV(char *ma, unsigned short soLuongKyTu, short x, short y)
{
    setbkcolor(15);
	setcolor(0);
    char tam;
    unsigned short i = strlen(ma);
    ma[i] = '|';
    ma[i+1] = '\0';
    while(1)
    {
        delay(10);
        outtextxy(x + 10, y + 7, ma);
        if (kbhit())
        {
            tam = getch();
            tam = toupper(tam);
            if (tam == BACKSPACE && i > 0){
                ma[i - 1] = '|';
                ma[i] = '\0';
                i--;
                xoa_input(x,y);
            }
            else if (tam == ESC){
				ma[0] = '\0';
				return;
			}
            else if (tam == ENTER)
			{
				if (i == 0){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.", "THONG BAO", MB_OK);
				}
				else{
					ma[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, ma);
					break;
				}
			}
            else if (tam >= 'A' && tam <= 'Z')
            {
                if (i == soLuongKyTu - 2) continue;
                ma[i] = tam;
                i++;
                ma[i] = '|';
                ma[i+1] = '\0';
            }
            else continue; // bỏ qua số và các kí tự khác
        }
    }
}

void Nhap_Gioi_Tinh(char *ma, unsigned short soLuongKyTu, short x, short y)
{
    setbkcolor(15);
	setcolor(0);
    char tam;
    unsigned short i = strlen(ma);
    ma[i] = '|';
    ma[i+1] = '\0';
    while(1)
    {
        delay(10);
        outtextxy(x + 10, y + 7, ma);
        if (kbhit())
        {
            tam = getch();
            tam = toupper(tam);
            if (tam == BACKSPACE && i > 0){
                ma[i - 1] = '|';
                ma[i] = '\0';
                i--;
                xoa_input(x,y);
            }
            else if (tam == ESC){
				ma[0] = '\0';
				return;
			}
            else if (tam == ENTER)
			{
				if (i == 0){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.NHAP : (NAM/NU).", "THONG BAO", MB_OK);
				}
				else if(i==1 || (i==2 && ma[i-1]=='A')) continue;
				else{
					ma[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, ma);
					break;
				}
			}// nu
            else if ((i==0 && tam=='N') || (i==1 && (tam == 'A' || tam =='U')) || (ma[1]=='A' && tam=='M'))
            {
                if (i == soLuongKyTu - 2) continue;
                ma[i] = tam;
                i++;
                ma[i] = '|';
                ma[i+1] = '\0';
            }
            else continue; // bỏ qua số và các kí tự khác
        }
    }
}

void NhapTinChi(unsigned short &so, short x, short y)
{
	setbkcolor(15);
	setcolor(0);
	char a[3];
    unsigned short i;
    if(so!=0)
    {
        itoa(so,a,10);
        i = strlen(a);
    }
    else
        i=0;
	a[i] = '|';
	a[i+1] = '\0';
	char tam;
    while (1){
		delay(10);
    	outtextxy(x + 10, y + 7, a);
		if (kbhit()){
    		tam = getch();
	        if (tam == BACKSPACE && i > 0)
			{
				a[i - 1] = '|';
				a[i] = '\0';
				i--;
				xoa_input(x,y);
			}
	        else if (tam == ENTER)
			{
				if (i == 0){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.", "THONG BAO", MB_OK);
				}
				else{
					a[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, a);
					break;
				}
			}
			else if (tam == ESC){
				so = 10;
				return;
			}
	        else if (i == 1) continue;
	        else if (tam >= '0' && tam <= '9'){
	            a[i] = tam;
				i++;
				a[i] = '|';
				a[i + 1] = '\0';
	        }
	        else continue;
		}
    }
    so = atoi(a);
}

void Nhap_TenMonHoc(char *ma, unsigned short soLuongKyTu, short x, short y)
{
    setbkcolor(15);
	setcolor(0);
    char tam;
    unsigned short i = strlen(ma);
    ma[i] = '|';
    ma[i+1] = '\0';
    while(1)
    {
        delay(10);
        outtextxy(x + 10, y + 7, ma);
        if (kbhit())
        {
            tam = getch();
            tam = toupper(tam);
            if (tam == BACKSPACE && i > 0){
                ma[i - 1] = '|';
                ma[i] = '\0';
                i--;
                xoa_input(x,y);
            }
            else if (tam == ESC){
				ma[0] = '\0';
				return;
			}
            else if (tam == ENTER)
			{
				if (i == 0){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.", "THONG BAO", MB_OK);
				}
				else{
					ma[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, ma);
					break;
				}
			} 
            else if ((tam == ' ' && i == 0) || (tam == ' ' && ma[i - 1] == ' ')) // bỏ khoảng trắng giữa và đầu
                continue;
            else if ((tam >= 'A' && tam <= 'Z') || (tam>='0' && tam<='9'))
            {
                if (i == soLuongKyTu - 2) continue;
                ma[i] = tam;
                i++;
                ma[i] = '|';
                ma[i+1] = '\0';
            }
            else if (tam == 32) // Nhận 1 khoảng trắng
            {
                ma[i] = tam;
                i++;
                ma[i] = '|';
                ma[i+1] = '\0';
            }
            else continue; // bỏ qua số và các kí tự khác
        }
    }
    if(ma[i-1]==' ')
        ma[i-1]=ma[i];
}

void Nhap_SDT(char *ma,unsigned short soLuongKyTu, short x, short y)
{
    setbkcolor(15);
	setcolor(0);
    char tam;
    unsigned short i = strlen(ma);
    ma[i] = '|';
    ma[i+1] = '\0';
    while(1)
    {
        delay(10);
        outtextxy(x + 10, y + 7, ma);
        if (kbhit())
        {
            tam = getch();
            if (tam == BACKSPACE && i > 0){
                ma[i - 1] = '|';
                ma[i] = '\0';
                i--;
                xoa_input(x,y);
            }
            else if (tam == ESC){
				ma[0] = '\0';
				return;
			}
            else if (tam == ENTER)
			{
				if (i == 0){
					MessageBeep(0xFFFFFFFF);
					MessageBox(NULL,"KHONG DUOC DE TRONG O NAY.", "THONG BAO", MB_OK);
                }
				else
                {
                    if(i!=soLuongKyTu - 2)
                    {
                        MessageBeep(0xFFFFFFFF);
                        MessageBox(NULL,"SO DIEN THOAI CHUA DU 10 SO.", "THONG BAO", MB_OK);
                        continue;
                    }
					ma[i] = '\0';
					xoa_input(x,y);
					outtextxy(x + 10,y + 7, ma);
					break;
				}
			}
            else if(tam >='0' && tam <='9')
            {
                if (i == soLuongKyTu - 2) continue;
                ma[i] = tam;
                i++;
                ma[i] = '|';
                ma[i+1] = '\0';
            }
            else continue;
        }
    }
}
