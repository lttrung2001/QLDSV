
#include <vector>
SINH_VIEN Khoi_tao_SV(SINH_VIEN &sv)
{
    sv.ma_sv[0] = '\0';
    sv.ho[0] = '\0';
    sv.ten[0] = '\0';
    sv.gioi_tinh[0] = '\0';
    sv.sdt[0] = '\0';
    return sv;
}
NODE_SV *Tao_Node_SV(SINH_VIEN &sv)
{
    NODE_SV *p = new NODE_SV;
    p->data = sv;
    p->next = NULL;
    return p;
}

NODE_SV *Check_maSV_TrongDSSV1(DS_SV &head_ds, char *ma) // kh?ng t?n t?i : NULL / t?n t?i :NODE_SV*
{
    if (head_ds == NULL)
        return NULL;
    NODE_SV *k = head_ds;
    while (k != NULL && !KiemTraTrungChuoi(k->data.ma_sv,ma))
        k = k->next;
    return (k==NULL) ? NULL : k ;
}

bool Check_maSV_TrongDSSV(DS_SV &head_ds, char *ma) // kh�ng t?n t?i : true / t?n t?i : false
{
    if (head_ds == NULL)
        return true;
    NODE_SV *k = head_ds;
    while (k != NULL && !KiemTraTrungChuoi(k->data.ma_sv,ma))
        k = k->next;
//    if(k==NULL)	return true;
//    else if(k->data.ma_sv)
    return (k == NULL) ? true : false;
}

void Them_NodeSV_Vao_DS(DS_SV &head_ds, SINH_VIEN &sv)
{
    NODE_SV *nodeThem=Tao_Node_SV(sv);
    if(head_ds==NULL)
    {
        head_ds=nodeThem;
        return;
    }
    NODE_SV *nodeChay=head_ds;
    NODE_SV *nodeTruoc=NULL;
    while(nodeChay!=NULL)
    {
        if(strcmp(nodeThem->data.ma_lop_sv,nodeChay->data.ma_lop_sv)<0)
            break;
        else if(strcmp(nodeThem->data.ma_lop_sv,nodeChay->data.ma_lop_sv)>0)
        {
            nodeTruoc=nodeChay;
            nodeChay=nodeChay->next;
        }
        else
        {
            if(strcmp(nodeThem->data.ten,nodeChay->data.ten)<0)
                break;
            else if(strcmp(nodeThem->data.ten,nodeChay->data.ten)>0)
            {
                nodeTruoc=nodeChay;
                nodeChay=nodeChay->next;
            }
            else
            {
                if(strcmp(nodeThem->data.ho,nodeChay->data.ho)<=0)
                    break;
                else if(strcmp(nodeThem->data.ho,nodeChay->data.ho)>0)
                {
                    nodeTruoc=nodeChay;
                    nodeChay=nodeChay->next;
                }
            }
        }
    }
    if(nodeTruoc==NULL) //  them dau
    {
        nodeThem->next=head_ds;
        head_ds=nodeThem;
    }
    else // them
    {    
        nodeThem->next=nodeChay;
        nodeTruoc->next=nodeThem;
    }
}

void Chuc_Nang_Them_SV_Theo_LOP(DS_SV &head_ds)
{
	SINH_VIEN sv;
    VeBangNhap("THEM SINH VIEN", "MA LOP");
	char ma_tam[17]; ma_tam[0] = '\0';
	NhapMa(ma_tam,17,1,XBANGNHAP,YBANGNHAP);
	XoaBang();
	if (ma_tam[0] == '\0') return;
	while (1){
		VeBangThem("THEM SINH VIEN",sinhVienLabel,SvLabelNum);
		sv = Khoi_tao_SV(sv);
		strcpy(sv.ma_lop_sv,ma_tam);
		setbkcolor(15);
		outtextxy(XBANGNHAP+10,YBANGNHAP+7,ma_tam);
		NhapMa(sv.ma_sv,17,1,XBANGNHAP,YBANGNHAP+50);
		if (sv.ma_sv[0] == '\0') return;
		while (1){
			if (!Check_maSV_TrongDSSV(head_ds,sv.ma_sv)){
				MessageBeep(0xFFFFFFFF);
				MessageBox(NULL,"MA SINH VIEN DA TON TAI.", "THONG BAO", MB_OK);
				NhapMa(sv.ma_sv,17,1,XBANGNHAP,YBANGNHAP+50);
				if (sv.ma_sv[0] == '\0') return;
			}
			else break;
		}
		Nhap_Ho_SV(sv.ho,32,XBANGNHAP,YBANGNHAP+100);
		if (sv.ho[0] == '\0') return;
		Nhap_Ten_SV(sv.ten,12,XBANGNHAP,YBANGNHAP+150);
		if (sv.ten[0] == '\0') return;
		Nhap_Gioi_Tinh(sv.gioi_tinh,5,XBANGNHAP,YBANGNHAP+200);
		if (sv.gioi_tinh[0] == '\0') return;
		// BAT DIEU KIEN GIOI TINH PHAI LA NAM HOAC NU
		Nhap_SDT(sv.sdt,12,XBANGNHAP,YBANGNHAP+250);
		if (sv.sdt[0] == '\0') return;
		Them_NodeSV_Vao_DS(head_ds,sv);
		MessageBox(NULL,"THEM SINH VIEN THANH CONG.", "THONG BAO", MB_OK);
	}
}

void InLopSVTheoDong(char *maLop,unsigned int &sl,short stt,short x,short y)
{
	char tam[5];
	outtextxy(x+40,y+12,itoa(stt,tam,10));
	x+=chonLopSize[0]; outtextxy(x+10,y+12,maLop);
	x+=chonLopSize[1]; outtextxy(x+80,y+12,itoa(sl,tam,10));
}

void InSvTheoDong1(SINH_VIEN sv, short x, short y) // bo bot ma lop sv
{
	char tam[10];
	outtextxy(x+20,y+12,sv.ma_sv);
	x += SVSIZE2[0]; outtextxy(x+5,y+12,sv.ho);
	x += SVSIZE2[1]; outtextxy(x+5,y+12,sv.ten);
	x += SVSIZE2[2]; outtextxy(x+20,y+12,sv.gioi_tinh);
	x += SVSIZE2[3]; outtextxy(x+20,y+12,sv.sdt);
}

void InSvTheoDong(SINH_VIEN sv, short x, short y)
{
	char tam[10];
	outtextxy(x+5,y+12,sv.ma_lop_sv);
	x += svSize[0]; outtextxy(x+5,y+12,sv.ma_sv);
	x += svSize[1]; outtextxy(x+5,y+12,sv.ho);
	x += svSize[2]; outtextxy(x+5,y+12,sv.ten);
	x += svSize[3]; outtextxy(x+5,y+12,sv.gioi_tinh);
	x += svSize[4]; outtextxy(x+5,y+12,sv.sdt);
}

void InThongTinSV(SINH_VIEN *sv)
{
    XoaBang();
	VeBangThem("THONG TIN SINH VIEN",sinhVienLabel,SvLabelNum);
	setbkcolor(15);
	setcolor(0);
	outtextxy(XBANGNHAP+10,YBANGNHAP+7, sv->ma_lop_sv);
	outtextxy(XBANGNHAP+10,YBANGNHAP+57, sv->ma_sv);
	outtextxy(XBANGNHAP+10,YBANGNHAP+107, sv->ho);
	outtextxy(XBANGNHAP+10,YBANGNHAP+157, sv->ten);
	outtextxy(XBANGNHAP+10,YBANGNHAP+207, sv->gioi_tinh);
	outtextxy(XBANGNHAP+10,YBANGNHAP+257, sv->sdt);
}

void in_DsLopSV(DS_SV &head_ds)
{
    if(head_ds==NULL)
    {
        // in thong bao khong co lop nao
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"KHONG CO LOP NAO.", "THONG BAO", MB_OK);
		return;
    }
    unsigned int dem = 1; // dem de cap phat vung nho cho amng cac lop  // 1 1
	unsigned int demSV=1; // ban dau =1 vi so sanh 2 sv cung 1 luc neu bang tang dem nen phai =1 luc dau moi dung
    for(NODE_SV *k=head_ds;k->next!=NULL;k=k->next) // dem sl lop de cap phat
    {
        if(!KiemTraTrungChuoi(k->data.ma_lop_sv,k->next->data.ma_lop_sv))
			dem++;
    }
	unsigned int sl[dem];// mang chua so luong sv 1 lop VD:cn01 co sl 80sv,...
    DS_SV maLop[dem]; // mang chua danh sach lop VD:cn01,cn02,cn03
	short VT=0;
	for(NODE_SV *k=head_ds;k->next!=NULL;k=k->next) // dem sl sinh vien trong 1 lop va do ra mang 1 1 1 2 2 2 
    {
        if(KiemTraTrungChuoi(k->data.ma_lop_sv,k->next->data.ma_lop_sv)) // dem SL SV 1 lop
            demSV++;
		else // ket thuc dem SV cua 1 lop, dua sang mang slsv de dem lop khac
		{
			sl[VT++]=demSV;
			demSV=1;
		}
		if(k->next->next==NULL) // ket thuc viec dem slsv cua lop cuoi cung trong dslkd
		{
			sl[VT++]=demSV;
			demSV=1;
		}
    }
	VT = 0; // GAN LAI =0 DE DufNG LAI
    maLop[VT]=head_ds;
	for (NODE_SV *k = head_ds->next;k != NULL; k = k->next){
		if (!KiemTraTrungChuoi(k->data.ma_lop_sv,maLop[VT]->data.ma_lop_sv))
			maLop[++VT] = k;
	}

	// in de cho chon
	char kytu;
	short chon = 0;
	short y;
	short i,j; // i la bien de dem sl con lai de in trang tiep theo
	// IN RA TRANG DAU TIEN
	loop:

	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,440, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,470, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,500, "DI CHUYEN");

	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"DANH SACH LOP",15,2);
	VeDauBang(chonLop,chonLopSize,chonLopNum,XMINTABLE,YDAUBANG);
	y = YTABLE;
	for (j = (chon/10)*10; j < ((chon/10)*10)+10 && j < dem; j++){
		VeDong(chonLopSize,chonLopNum,XMINTABLE,y,0);
		InLopSVTheoDong(maLop[j]->data.ma_lop_sv,sl[j],j+1,XMINTABLE,y);
		y+=DONG;
	}
	VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
	InLopSVTheoDong(maLop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
	// ham in lop SV theo dong
	while (1)
	{
		delay(10);
		if(kbhit())
		{
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu)
			{
				case KEY_UP:
					if (chon > 0){
						if (chon % 10 == 0)
						{
							XoaBangDuLieu();
							chon--;
							y = YTABLE;
							for (j = chon-9; j <= chon; j++)
							{
								VeDong(chonLopSize,chonLopNum,XMINTABLE,y,0);
								InLopSVTheoDong(maLop[j]->data.ma_lop_sv,sl[j],j+1,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLopSVTheoDong(maLop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLopSVTheoDong(maLop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon--;
						VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLopSVTheoDong(maLop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case KEY_DOWN:
					if (chon + 1 < dem){
						if ((chon + 1) % 10 == 0)
						{
							XoaBangDuLieu();
							chon++;
							i = dem - chon >= 10 ? 10 : dem - chon;
							y = YTABLE;
							for (j = chon; j < chon + i; j++)
							{
								VeDong(chonLopSize,chonLopNum,XMINTABLE,y,0);
								InLopSVTheoDong(maLop[j]->data.ma_lop_sv,sl[j],j+1,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLopSVTheoDong(maLop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLopSVTheoDong(maLop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon++;
						VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLopSVTheoDong(maLop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case ESC:
					XoaBang();
					return;
				case ENTER:{
					XoaHDSD();
					setcolor(0);
					setbkcolor(15);
					outtextxy(xMenuChinh+5,440, "DUNG MUI TEN");
					outtextxy(xMenuChinh+5,470, "LEN XUONG DE");
					outtextxy(xMenuChinh+5,500, "SANG TRANG");

					short stackNum = 0;
					DS_SV ds_nodeDauTrang[sl[chon]/10]; // MANG TAM DE LUU CAC NODE DAU CUA 1 TRANG TRONG DANH SACH
					DS_SV nodeChay = maLop[chon]; // chay
					DS_SV nodeDau = nodeChay; // so sanh voi chay de in
					XoaBang();
					textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG/2,"DANH SACH SINH VIEN",15,2);
					textcenter(XMINTABLE,YDAUBANG/2,XMAXTABLE,100,"LOP: " + convertToString(nodeChay->data.ma_lop_sv),2,15);
					VeDauBang(SINHVIENLABEL2,SVSIZE2,SvLabelNum-1,XMINTABLE,YDAUBANG);
					y = YTABLE;
					for (j = 0; j < 10 && nodeChay != NULL && KiemTraTrungChuoi(nodeDau->data.ma_lop_sv,nodeChay->data.ma_lop_sv); j++){ // IN CAC PHAN TU THEO 1 TRANG
						VeDong(SVSIZE2,SvLabelNum-1,XMINTABLE,y,0);
						InSvTheoDong1(nodeChay->data,XMINTABLE,y);
						nodeChay = nodeChay->next;
						y+=DONG;
					}
					
					while (1){
						delay(10);
						if (kbhit()){
							kytu = getch();
							if (kytu == -32) kytu = getch();
							switch(kytu){
								case KEY_UP:
									if (stackNum > 0){
										nodeChay = ds_nodeDauTrang[--stackNum];
										nodeDau = nodeChay;
										XoaBangDuLieu();
										y = YTABLE;
										for (j = 0; j < 10 && nodeChay != NULL && KiemTraTrungChuoi(nodeDau->data.ma_lop_sv,nodeChay->data.ma_lop_sv); j++){
											VeDong(SVSIZE2,SvLabelNum-1,XMINTABLE,y,0);
											InSvTheoDong1(nodeChay->data,XMINTABLE,y);
											nodeChay = nodeChay->next;
											y+=DONG;
										}
									}
									break;
								case KEY_DOWN:
									if (nodeChay != NULL && KiemTraTrungChuoi(nodeDau->data.ma_lop_sv,nodeChay->data.ma_lop_sv)){
										ds_nodeDauTrang[stackNum++] = nodeDau;
										nodeDau = nodeChay;
										XoaBangDuLieu();
										y = YTABLE;
										for (j = 0; j < 10 && nodeChay != NULL && KiemTraTrungChuoi(nodeDau->data.ma_lop_sv,nodeChay->data.ma_lop_sv); j++){
											VeDong(SVSIZE2,SvLabelNum-1,XMINTABLE,y,0);
											InSvTheoDong1(nodeChay->data,XMINTABLE,y);
											nodeChay = nodeChay->next;
											y+=DONG;
										}
									}
									break;
								case ESC:
									XoaHDSD();
									goto loop;
							}
						}
					}
				}
			}
		}
	}
}

void Xoa_NODE_SV_Theo_maSV(DS_SV &head_ds, char *ma)
{
    if(head_ds==NULL)
    	return;
    DS_SV chay=head_ds;
    DS_SV truoc=NULL;
    while(chay!=NULL)
    {
    	if(!KiemTraTrungChuoi(chay->data.ma_sv,ma))
    	{
    		truoc=chay;
    		chay=chay->next;
		}
		else
			break;
	}
	if(truoc==NULL) // xoa dau
	{
		head_ds=head_ds->next;
		delete chay;
		chay=NULL;
	}
	else
	{
		truoc->next=chay->next;
		delete chay;
		chay=NULL;
	}
}

void Xoa_NODE_DK(DS_SVDK &head_ds, char *ma)
{
    if(head_ds==NULL)
    	return;
    DS_SVDK chay=head_ds;
    DS_SVDK truoc=NULL;
    while(chay!=NULL)
    {
    	if(!KiemTraTrungChuoi(chay->data.ma_sv,ma))
    	{
    		truoc=chay;
    		chay=chay->next;
		}
		else
			break;
	}
	if(truoc==NULL) // xoa dau
	{
		head_ds=head_ds->next;
		delete chay;
		chay=NULL;
	}
	else
	{
		truoc->next=chay->next;
		delete chay;
		chay=NULL;
	}
}

int ChucNangTimSV(DS_SV &head_ds,SINH_VIEN *&sv,string ThongBao) // cho chon new
{
	char maSV[17];
	maSV[0]='\0';
	XoaBang();
	VeBangNhap(ThongBao,"MA SINH VIEN");
	NhapMa(maSV,17,1,XBANGNHAP,YBANGNHAP);
	if(maSV[0]=='\0')	return -1;
	NODE_SV *tim;
	tim=Check_maSV_TrongDSSV1(head_ds,maSV);
	while(tim==NULL)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"SINH VIEN KHONG TON TAI.", "THONG BAO", MB_OK);
		NhapMa(maSV,17,1,XBANGNHAP,YBANGNHAP);
		if(maSV[0]=='\0')	return -1;
		tim=Check_maSV_TrongDSSV1(head_ds,maSV);
	}
	sv=&(tim->data);
}

int TimKiemNhiPhanLop(SINH_VIEN *arrDSSV[],int left,int right,char *maLopSV)
{
	if(right >= left )
	{
		int mid=left + (right-left)/2;
		if(strcmp(arrDSSV[mid]->ma_lop_sv,maLopSV)==0) // tim thay nhung phai di tim ndoe dau lop nua
		{
			if(mid==0) return mid;
			else
			{
				int chayQuaTrai=mid-1;
				while(1)
				{
					if(strcmp(arrDSSV[mid]->ma_lop_sv,arrDSSV[chayQuaTrai]->ma_lop_sv)!=0)
						return chayQuaTrai+1;
					else
						chayQuaTrai--;
				}
			}
		}
		if(strcmp(arrDSSV[mid]->ma_lop_sv,maLopSV)>0)
			return TimKiemNhiPhanLop(arrDSSV,left,mid-1,maLopSV);
		return TimKiemNhiPhanLop(arrDSSV,mid+1,right,maLopSV);
	}
	return -1;
}

int ChucNangLocSV(DS_SV &head_ds,SINH_VIEN *arrDSSV[],string ThongBao,int &demSV) // cho chon new
{
	char maLopSV[17];
	int viTri=0;
	maLopSV[0]='\0';
	XoaBang();
	VeBangNhap(ThongBao,"MA LOP");
	NhapMa(maLopSV,17,1,XBANGNHAP,YBANGNHAP);
	if(maLopSV[0]=='\0')	return -2;
	viTri=TimKiemNhiPhanLop(arrDSSV,0,demSV-1,maLopSV);
	return viTri;
}

int ChucNangSuaInfoSV(DS_LOP_TC &dsltc,DS_SV &head_ds,SINH_VIEN *ds[],SINH_VIEN &sv,int demSV)
{
	SINH_VIEN NewData;
	bool check;
	NewData=sv;
	XoaBang();
	VeBangThem("SUA THONG TIN SINH VIEN",sinhVienLabel,SvLabelNum);
	setbkcolor(15); setcolor(0);
	outtextxy(XBANGNHAP+10,YBANGNHAP+7,sv.ma_lop_sv);
	outtextxy(XBANGNHAP+10,YBANGNHAP+57,sv.ma_sv);
	outtextxy(XBANGNHAP+10,YBANGNHAP+107,sv.ho);
	outtextxy(XBANGNHAP+10,YBANGNHAP+157,sv.ten);
	outtextxy(XBANGNHAP+10,YBANGNHAP+207,sv.gioi_tinh);
	outtextxy(XBANGNHAP+10,YBANGNHAP+257,sv.sdt);								
	NhapMa(NewData.ma_lop_sv,17,1,XBANGNHAP,YBANGNHAP);
	if(NewData.ma_lop_sv[0]=='\0')
		return -1;
	do
	{
		NhapMa(NewData.ma_sv,17,1,XBANGNHAP,YBANGNHAP+50);
		if(KiemTraTrungChuoi(NewData.ma_sv,sv.ma_sv)) // neu khong sua ma sv hoac nhap ma van la ma sv cu thi bo qua va cho nhap ca thong tin con lai
			break;
		else
		{
			check=Check_maSV_TrongDSSV(head_ds,NewData.ma_sv);
			if(!check)
			{
				MessageBeep(0xFFFFFFFF);
				MessageBox(NULL,"MA SINH VIEN DA TON TAI.", "THONG BAO", MB_OK);
			}
		}
	}while(!check);									
	if(NewData.ma_sv[0]=='\0')  // de quay lai xem data
		return -1;
	Nhap_Ho_SV(NewData.ho,32,XBANGNHAP,YBANGNHAP+100);
	if (NewData.ho[0] == '\0') 
		return -1;
	Nhap_Ten_SV(NewData.ten,12,XBANGNHAP,YBANGNHAP+150);
	if (NewData.ten[0] == '\0')
		return -1;
	Nhap_Gioi_Tinh(NewData.gioi_tinh,5,XBANGNHAP,YBANGNHAP+200);
	if (NewData.gioi_tinh[0] == '\0')
		return -1;
	// BAT DIEU KIEN GIOI TINH PHAI LA NAM HOAC NU
	Nhap_SDT(NewData.sdt,12,XBANGNHAP,YBANGNHAP+250);
	if (NewData.sdt[0] == '\0')	
		return -1;
	SuaSVTrenMang(ds,sv.ma_sv,NewData,demSV);
	if(!KiemTraTrungChuoi(NewData.ma_sv,sv.ma_sv)) // neu ma sv moi khac ma sv cu sua tren danh sach dang ki, con khong thi thoi
		Sua_Tren_DSSVDK(dsltc,sv.ma_sv,NewData.ma_sv); // thay tam = sv
	MessageBox(NULL,"SUA THONG TIN SINH VIEN THANH CONG", "THONG BAO", MB_OK);
}

void Sua_Tren_DSSVDK(DS_LOP_TC &ds,char *maSV_Cu,char *maSV_Moi)
{
	unsigned int i=0;
	DS_SVDK nodeChay = NULL;
	for(i;i<ds.n_loptc;i++)
	{
		nodeChay=ds.ds_ltc[i]->ds_svdk;
		while(nodeChay !=NULL && !KiemTraTrungChuoi(nodeChay->data.ma_sv,maSV_Cu))
			nodeChay=nodeChay->next;
		if(nodeChay==NULL)
			continue;
		else
			strcpy(nodeChay->data.ma_sv,maSV_Moi);
	}
}

void SuaSVTrenMang(SINH_VIEN *ds[],char *maSVcu,SINH_VIEN sv,int demSV)
{
	int i=0; // vitri cu
	int j=0;// vitri moi
	while(i>=0 && !KiemTraTrungChuoi(ds[i]->ma_sv,maSVcu)) // tim vitri cu
		i++;
	while(j>=0 && j < demSV) // tim vitri moi
	{
		if(strcmp(sv.ma_lop_sv,ds[j]->ma_lop_sv)>0)
			j++;
		else if(strcmp(sv.ma_lop_sv,ds[j]->ma_lop_sv)==0) // bang 
		{
			if(strcmp(sv.ten,ds[j]->ten)>0)
				j++;
			else if(strcmp(ds[j]->ten,sv.ten)==0)// bang ten xet den ho
			{
				if(strcmp(sv.ho,ds[j]->ho)>0)
					j++;
				else if(strcmp(sv.ho,ds[j]->ho)<=0) break;
			}
			else break;
		}
		else break; // < 0
	}
	while(i<j-1) // truong hop doi data o tren xuong duoi, j-1 : la boi vi viTriDung < vitrij, tuc o node truoc j.
	{
		*ds[i]=*ds[i+1];
		i++;
	}
	while(i>j) //truong hop doi data duoi len tren, khong can j-1 boi vi can dung dusng vi tri j, j > vitridung len ve sau
	{
		*ds[i]=*ds[i-1];
		i--;
	}
	*ds[i]=sv;
}

void SelectSV(DS_LOP_TC &dsltc,DS_SV &head_ds)
{
	if(head_ds==NULL)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "KHONG CO SINH VIEN NAO TRONG DANH SACH.", "THONG BAO", MB_OK);
		return;
	}
	int i,j,demSV=0,chon=0;
	short  y, a;//i :duyet,... a: messbox
	int GoTo;
	bool check;
	char kytu;
	i = 0;
	for(NODE_SV *nodeChay=head_ds;nodeChay!=NULL;nodeChay=nodeChay->next)
		demSV++;
	SINH_VIEN *arrDSSV[demSV]; // mang con tro tro den data cua tung node sinh vien
	for(NODE_SV *nodeChay=head_ds;nodeChay!=NULL;nodeChay=nodeChay->next)
		arrDSSV[chon++]=&(nodeChay->data);
	chon=0;
	SINH_VIEN *sv;
	SinhVien:
	if(demSV==0)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "KHONG CO SINH VIEN NAO TRONG DANH SACH.", "THONG BAO", MB_OK);
		return;
	}
	if(chon==demSV)
		chon--;
	
	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,440, "F1: TIM KIEM SV");
	outtextxy(xMenuChinh+5,470, "F2: SUA SV");
	outtextxy(xMenuChinh+5,500, "F3: XOA SV");
	outtextxy(xMenuChinh+5,530, "F4: TIM LOP SV");
	outtextxy(xMenuChinh+5,560, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,590, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,620, "DI CHUYEN");

	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"DANH SACH SINH VIEN TOAN TRUONG",15,2);
	VeDauBang(sinhVienLabel,svSize,SvLabelNum,XMINTABLE,YDAUBANG);
	y = YTABLE;
	for (i = (chon/10)*10; i < ((chon/10)*10)+10 && i < demSV; i++)
	{ // IN CAC PHAN TU THEO 1 TRANG
		VeDong(svSize,SvLabelNum,XMINTABLE,y,0);
		InSvTheoDong(*arrDSSV[i],XMINTABLE,y);
		y+=DONG;
	}
	VeDong(svSize,SvLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
	InSvTheoDong(*arrDSSV[chon],XMINTABLE,YTABLE+((chon%10)*DONG));
	while (1)
	{
		delay(10);
		if (kbhit())
		{
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu)
			{
				case KEY_UP:
					if (chon>0)
					{
						if(chon%10==0)
						{
							XoaBangDuLieu();
							chon--;
							y = YTABLE;
							for (i = chon-9; i <= chon; i++)
							{ // IN CAC PHAN TU THEO 1 TRANG
								VeDong(svSize,SvLabelNum,XMINTABLE,y,0);
								InSvTheoDong(*arrDSSV[i],XMINTABLE,y);
								y+=DONG;
							}
							VeDong(svSize,SvLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InSvTheoDong(*arrDSSV[chon],XMINTABLE,YTABLE+((chon%10)*DONG));
							break;
						}
						// y = YTABLE;
						VeDong(svSize,SvLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InSvTheoDong(*arrDSSV[chon],XMINTABLE,YTABLE+((chon%10)*DONG));
						chon--;
						VeDong(svSize,SvLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InSvTheoDong(*arrDSSV[chon],XMINTABLE,YTABLE+((chon%10)*DONG));
					}
					break;
				case KEY_DOWN:
					if (chon +1 <demSV )
					{
						if((chon+1)%10==0)
						{
							XoaBangDuLieu();
							chon++;
							j = demSV-chon>=10?10:demSV-chon;
							y = YTABLE;
							for (i = chon; i < chon + j; i++)
							{ // IN CAC PHAN TU THEO 1 TRANG
								VeDong(svSize,SvLabelNum,XMINTABLE,y,0);
								InSvTheoDong(*arrDSSV[i],XMINTABLE,y);
								y+=DONG;
							}
							VeDong(svSize,SvLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InSvTheoDong(*arrDSSV[chon],XMINTABLE,YTABLE+((chon%10)*DONG));
							break;
						}
						// y = YTABLE;
						VeDong(svSize,SvLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InSvTheoDong(*arrDSSV[chon],XMINTABLE,YTABLE+((chon%10)*DONG));
						chon++;
						VeDong(svSize,SvLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InSvTheoDong(*arrDSSV[chon],XMINTABLE,YTABLE+((chon%10)*DONG));
					}
					break;
				case KEY_F1://tim kiem
					GoTo=ChucNangTimSV(head_ds,sv,"TIM KIEM SINH VIEN");
					if(GoTo==-1)
						goto SinhVien;
					InThongTinSV(sv);

					while(1)
					{
						if(kbhit())
						{
							kytu=getch();
							if(kytu==-32) kytu=getch();
							switch (kytu)
							{
								case KEY_F2:
									GoTo=ChucNangSuaInfoSV(dsltc,head_ds,arrDSSV,*sv,demSV);
									if(GoTo==-1)
										goto SinhVien;
									goto SinhVien;
								case KEY_F3: // xoa sinh vien
									check=ChucNangXoaSV(dsltc,head_ds,arrDSSV,*sv,demSV);
									if(!check)
									{
										MessageBeep(0xFFFFFFFF);
										MessageBox(NULL, "HUY XOA SINH VIEN THANH CONG.", "THONG BAO", MB_OK);
										goto SinhVien;
									}
									else if(check)
									{
										MessageBeep(0xFFFFFFFF);
										MessageBox(NULL, "XOA SINH VIEN THANH CONG.", "THONG BAO", MB_OK);
										goto SinhVien;
									}
									break;
								case ESC:
									goto SinhVien;
							}
						}
					}
					break;
				case KEY_F2:
					GoTo=ChucNangSuaInfoSV(dsltc,head_ds,arrDSSV,*arrDSSV[chon],demSV);
					if(GoTo==-1)
						goto SinhVien;
					goto SinhVien;
				case KEY_F3: // xoa sinh vien
					check=ChucNangXoaSV(dsltc,head_ds,arrDSSV,*arrDSSV[chon],demSV);
					if(!check)
					{
						MessageBeep(0xFFFFFFFF);
						MessageBox(NULL, "HUY XOA SINH VIEN THANH CONG.", "THONG BAO", MB_OK);
						goto SinhVien;
					}
					else if(check)
					{
						MessageBeep(0xFFFFFFFF);
						MessageBox(NULL, "XOA SINH VIEN THANH CONG.", "THONG BAO", MB_OK);
						goto SinhVien;
					}
				case KEY_F4: // loc danh sach , moi nhap ma lop sv
					GoTo=ChucNangLocSV(head_ds,arrDSSV,"TIM LOP CUA SINH VIEN",demSV);
					if(GoTo==-1)
					{
						MessageBeep(0xFFFFFFFF);
						MessageBox(NULL, "KHONG TIM THAY LOP SINH VIEN TUONG UNG", "THONG BAO", MB_OK);
						goto SinhVien;
					}
					else if(GoTo==-2)
						goto SinhVien;
					else
					{
						chon=GoTo;
						goto SinhVien;
					}
				case ESC:
					XoaBang();
					return;
			}
		}
	}
}

int KiemTra_SVCoDiemChua(DS_SVDK &head_ds,char *maSV){
    if (head_ds == NULL) return 0;
    DS_SVDK nodeChay = head_ds;
    while (nodeChay != NULL && !KiemTraTrungChuoi(nodeChay->data.ma_sv,maSV))
		nodeChay=nodeChay->next;
	if(nodeChay==NULL) // k co sv trong lop tin chi nay
		return 0;
	return (nodeChay->data.diem==-1) ? -1:1; // chua co diem -1, co thi 1;
}

bool ChucNangXoaSV(DS_LOP_TC &dsltc,DS_SV &head_ds,SINH_VIEN *dssv[],SINH_VIEN sv,int &demSV) // moi cho chon
{
	int a,KiemTra=0,j=0; //a : mess,KiemTra de check,j la bien vitri.
	unsigned int i=0;
	unsigned int dem=0;// dem sl lop tin chi ma sv can xoa nay dang ki
	vector<unsigned int> ViTri;
	for(i;i<dsltc.n_loptc;i++)
	{
		KiemTra=KiemTra_SVCoDiemChua(dsltc.ds_ltc[i]->ds_svdk,sv.ma_sv);
		if(KiemTra!=0)
		{
			dem++;
			ViTri.resize(dem);
			ViTri[dem-1]=i;
		}
	}
	
	i=0;
	for(i=0;i<dem;i++)
	{
		KiemTra=KiemTra_SVCoDiemChua(dsltc.ds_ltc[ViTri[i]]->ds_svdk,sv.ma_sv);
		if(KiemTra==1) // co diem
		{
			a=MessageBox(NULL, "SINH VIEN NAY DA CO DIEM,BAN CO CHAC CHAN MUON XOA KHONG?", "THONG BAO", MB_YESNO);
			break;
		}
	}
	i=0;
	if(KiemTra==-1 || KiemTra==0 )
		a=MessageBox(NULL, "BAN CO CHAC CHAN MUON XOA KHONG?", "THONG BAO", MB_YESNO);
	
	if(a==6) // -> YES
	{
		while(i<dem)
		{
			Xoa_NODE_DK(dsltc.ds_ltc[ViTri[i]]->ds_svdk,sv.ma_sv);
			i++;
		}
		while(j>=0 && !KiemTraTrungChuoi(dssv[j]->ma_sv,sv.ma_sv)) // luu lai vi tri de ti xoa tren mang
			j++;
		Xoa_NODE_SV_Theo_maSV(head_ds,sv.ma_sv);
		while(j<demSV-1)
		{
			dssv[j]=dssv[j+1];
			j++;
		}
		demSV--;
		return true;
	}
	else
		return false;
}

void Doc_FILE_DSSV(DS_SV &head_ds)
{
    SINH_VIEN sv;
    ifstream filein("dsSV.txt");
    while(!filein.eof())
    {
        sv = Khoi_tao_SV(sv);
        filein.getline(sv.ma_lop_sv, 16, ' ');
        if(sv.ma_lop_sv[0]=='\0') // khong them 1 dua rong du lieu vao cuoi
            return;
        filein.getline(sv.ma_sv, 16, ' ');
        filein.getline(sv.ho, 31,'-');
        filein.getline(sv.ten, 11, ' ');
        filein.getline(sv.gioi_tinh, 4, ' ');
        filein.getline(sv.sdt, 11, '\n');
        Them_NodeSV_Vao_DS(head_ds,sv);
    }
    filein.close();
}

void Ghi_FILE_DSSV(DS_SV &head_ds)
{
    ofstream fileout("dsSV.txt");
    for(NODE_SV *k=head_ds;k!=NULL;k=k->next)
    {
        fileout<<k->data.ma_lop_sv<<' ';
        fileout<<k->data.ma_sv<<' ';
        fileout<<k->data.ho<<'-';
        fileout<<k->data.ten<<' ';
        fileout<<k->data.gioi_tinh<<' ';
        fileout<<k->data.sdt;
        fileout<<'\n';
    }
    fileout.close();
}
