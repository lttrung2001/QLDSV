MON_HOC khoi_taoMH(MON_HOC &mon)
{
    mon.ma_mh[0] = '\0';
    mon.ten_mh[0] = '\0';
    mon.stc_lt = 0;
    mon.stc_th = 0;
    return mon;
}

TREE Tao_NODE_MonHoc(MON_HOC &mon)
{
    TREE p = new NODE_MH;
    p->data = mon;
    p->L = p->R = NULL;
    return p;
}

void Them_MonHoc(TREE &goc, MON_HOC &mon)
{
	int numThemVao=atoi(mon.ma_mh);
	int numChay=0;
	TREE nodeMoi = Tao_NODE_MonHoc(mon);
	if (goc == NULL) goc = nodeMoi;
	else  // Goc != NULL
	{
		TREE nodeChay = goc;
		TREE nodeTruoc = NULL;
		while (nodeChay != NULL)
		{
			numChay=atoi(nodeChay->data.ma_mh);
			nodeTruoc = nodeChay;
			if(numChay<0) 
				numChay*=(-1);
			if (numThemVao > numChay ) 
				nodeChay = nodeChay->R;
			else if(numThemVao < numChay)
				nodeChay = nodeChay->L;
			else if(numChay==numThemVao)
			{
				nodeChay->data=nodeMoi->data;
				delete nodeMoi;
				return;
			}
		}
		if (atoi(nodeMoi->data.ma_mh) > atoi(nodeTruoc->data.ma_mh)) nodeTruoc->R = nodeMoi;
		else nodeTruoc->L = nodeMoi;
	}
}

void DemNodeDuong(TREE &goc,int &dem)
{
	if(goc==NULL) return;
	else
	{
		if(atoi(goc->data.ma_mh)>0)
			dem++;
		// else if(atoi(goc->data.ma_mh)<0)
		// 	dem-1;
		DemNodeDuong(goc->L,dem);
		DemNodeDuong(goc->R,dem);
	}
}

int TimNodeAm(TREE &goc)
{
	if(goc==NULL) return 1;
	int num=atoi(goc->data.ma_mh);
	if(num < 0)
		return num;
	else if(goc->R!=NULL)
	{
		num=atoi(goc->R->data.ma_mh);
		if(num<0)
			return  num;
	}
	else if(goc->L!=NULL)
	{
		TREE nodeChay=goc->L;
		while(nodeChay!=NULL)
		{
			num=atoi(nodeChay->data.ma_mh);
			if(num<0)// nhung node ben trai cung cua cay
				return num;
			else
				nodeChay=nodeChay->L;
		}
	}
	return 1; // di het la k cos node am thi return duong
}

void LayGiaTriTrai(TREE &t, int& x1, int& x2) // x1: gia tri goc ,x2 gia tri ben trai goc
{
	if (t == NULL)
		return;
	TREE nodeChay=t;
	while(nodeChay != NULL)
	{
		if (nodeChay->L != NULL)
		{
			x1 = atoi(nodeChay->data.ma_mh); 
			x2 = atoi(nodeChay->L->data.ma_mh);
		}
		else if (nodeChay->L == NULL)
		{
			x2 = atoi(nodeChay->data.ma_mh);
			return;
		}
		nodeChay=nodeChay->L;
	}	
}

int Lay_Ma_MonHoc(TREE t, int n,int &chieuCao,int &tongNode,int &viTriLa)  
{
	TREE tam=t; 
	if(tongNode==0)
		return n;
	int x3,x2,x1 = n;
	 // x2 la gia tri ben trai cua x1
	 // x3 la node co gia tri can them vao tiep theo
//	int viTriLa;
	LayGiaTriTrai(t, x1, x2);
	//pow(2,chieuCao-1) : tuc la so luong node la can co tren bac dang xet vd:bac 2 : 2 node,bac 3: 4 node ,bac 4 : 8 node ...
	//pow(2,chieuCao) -1 : tuc la so luong node toi da tu bac 1 den bac dang xet ,vd:bac 2 : 3node,bac 3 : 7node,...

	// viTriLa = pow(2, chieuCao - 1) - pow(2, chieuCao) + tongNode + 1 + soNodeXoa ; // lu?n bat dau tu vitri 1 den vitri so pow(2,chieuCao-1) -1; 
	/* vi du
													goc
								2^(1-1)								1 (pow(2,1-1) -1)
						2^(2-1)				1				2					3 (pow(2,2-1) -1)
				2^(3-1)				1				2			3			4			5(pow(2,3-1) -1)

	*/
	if(viTriLa==(pow(2,chieuCao-1))) // node o vi tri so 0 tuc la node ben trai cung cua cay
		x3 = ((x2-100000)/2)+100000;
	else // cac vi tri tu 1 den 2^(chieuCao-1)-1
		x3=x2+((x1-100000)*viTriLa)+(viTriLa/2);
	return x3;		
}

void ChucNang_ThemMonHoc(TREE &goc,int &chieuCao,int &tongNode)
{
	MON_HOC mon;
	int maMH=0,viTriLa=0;
	bool check;// de kiem tra neu false tuc la ma MH la am thi them nhung k duoc tang tongNode len se bi bo qua,sai.
	while(1)
	{
		XoaBang();
		maMH=TimNodeAm(goc);
		if(maMH==1)
		{
			check=true;
			viTriLa = pow(2, chieuCao - 1) - pow(2, chieuCao) + tongNode + 1 ;
			maMH=Lay_Ma_MonHoc(goc,500000,chieuCao,tongNode,viTriLa);
		}
		else if(maMH<0)
		{
			maMH*=(-1);
			check=false;
		}
		VeBangThem("THEM MON HOC",monHocLabel,MhLabelNum);
		mon=khoi_taoMH(mon);
		setbkcolor(15);
		outtextxy(XBANGNHAP+10,YBANGNHAP+7,itoa(maMH,mon.ma_mh,10));
		itoa(maMH,mon.ma_mh,10);
		Nhap_TenMonHoc(mon.ten_mh,52,XBANGNHAP,YBANGNHAP+50);
		if(mon.ten_mh[0]=='\0')
			return;
		NhapTinChi(mon.stc_lt,XBANGNHAP,YBANGNHAP+100);
		if(mon.stc_lt==10)
			return;
		NhapTinChi(mon.stc_th,XBANGNHAP,YBANGNHAP+150);
		if(mon.stc_th==10)
			return;
		Them_MonHoc(goc,mon);
		MessageBox(NULL,"THEM MON HOC THANH CONG.", "THONG BAO", MB_OK);
		if(viTriLa==(pow(2,chieuCao-1))) 
			chieuCao++;
		if(check)
			tongNode++;
	}
}

bool is_empty(ifstream& pFile) // kiem tra file co du lieu hay khong
{
    return pFile.peek() == ifstream::traits_type::eof(); 
	// peek :  doc k� t? ti?p theo m� k c?n gi?i n�n n�
}

void Doc_FILE_MonHoc(TREE &t)
{
    MON_HOC mon;
    ifstream filein("dsMH.txt");
	if (is_empty(filein))
	{
		filein.close();
		return;
	}
    while (!filein.eof())
    {
       	mon = khoi_taoMH(mon);
        filein.getline(mon.ma_mh, 16, '\n');
        // filein.ignore();
        filein.getline(mon.ten_mh, 51, '\n');
        filein >> mon.stc_lt;
        filein.ignore();
        filein >> mon.stc_th;
        filein.ignore();
		if(mon.ma_mh[0]=='\0')
			break;
        Them_MonHoc(t,mon);
    }
    filein.close();
}

void Doc_FILE_Num(int &chieuCao,int &tongNode)
{
	ifstream filein("filenumber.txt");
	if (is_empty(filein))
	{
		filein.close();
		return;
	}
	while(!filein.eof())
	{
		filein>>chieuCao;
		filein.ignore();
		filein>>tongNode;
	}
	filein.close();
}

void Ghi_FILE_NLR(ofstream &file, TREE t)
{
    if (t != NULL)
    {
        file << t->data.ma_mh << endl;
        file << t->data.ten_mh << endl;
        file << t->data.stc_lt << endl;
        file << t->data.stc_th << endl;
        Ghi_FILE_NLR(file, t->L);
        Ghi_FILE_NLR(file, t->R);
    }
}

void Ghi_FILE_MonHoc(TREE &t)
{
    ofstream fileout("dsMH.txt", ios::out);
    fileout.clear();
    Ghi_FILE_NLR(fileout, t);
    fileout.close();
}

void Ghi_FILE_num(int &chieuCao,int &tongNode)
{
	ofstream fileout("filenumber.txt");
	fileout.clear();
	fileout<<chieuCao<<endl;
	fileout<<tongNode;
	fileout.close();
}

void DoTreeRaMangConTro(TREE t,TREE ds[], int &n_ds)
{
    // Duy?t theo L-N-R
    if (t == NULL)
        return;
    else
    {
		if(atoi(t->data.ma_mh)>0)
        	ds[n_ds++] = t;
        DoTreeRaMangConTro(t->L, ds, n_ds);
        DoTreeRaMangConTro(t->R, ds, n_ds);
    }
}

void swapDataMH(MON_HOC &a,MON_HOC &b)
{
	MON_HOC tam=a;
   a = b;
   b = tam;
}

void SapXepMonHocTheo_TenMonHoc(TREE ds[], int &n_ds)
{
    int i, j, min_idx;
    // Di chuy?n ranh gi?i c?a m?ng d? s?p x?p v? chua s?p x?p
    for (i = 0; i < n_ds-1; i++)
    {
    // T?m ph?n t? nh? nh?t trong m?ng chua s?p x?p
    min_idx = i;
    for (j = i+1; j < n_ds; j++)
        //if (ds[j] < ds[min_idx])
        if(stricmp(ds[j]->data.ten_mh, ds[min_idx]->data.ten_mh) < 0)
            min_idx = j;
    // ??i ch? ph?n t? nh? nh?t v?i ph?n t? d?u ti?n
		if(min_idx != i)
		{
			TREE tam=ds[i];
			ds[i]=ds[min_idx];
			ds[min_idx]=tam;
		}	
    }
}

void InThongTin_MotMonHoc(MON_HOC mon,short x,short y)
{
	char tam[5];
	outtextxy(x+50,y+12,mon.ma_mh);
	x+=mhSize[0];outtextxy(x+10,y+12,mon.ten_mh);
	x+=mhSize[1];outtextxy(x+45,y+12,itoa(mon.stc_lt,tam,10));
	x+=mhSize[2];outtextxy(x+45,y+12,itoa(mon.stc_th,tam,10));
}

void In_DsMonHoc(TREE &goc)
{
	int demNode=0;
	int number=0;
	DemNodeDuong(goc,demNode);
	if(goc==NULL || demNode ==0)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"DANH SACH MON HOC RONG.", "THONG BAO", MB_OK);
		return;
	}
	TREE ds[demNode];
	DoTreeRaMangConTro(goc,ds,number);
	SapXepMonHocTheo_TenMonHoc(ds,demNode);
	char kytu;
	short x,y;
	int i,j=0; // i la bien de dem sl con lai de in trang tiep theo
	MonHoc:
	if(demNode == 0)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"DANH SACH MON HOC RONG.", "THONG BAO", MB_OK);
		return;
	}
	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"DANH SACH MON HOC",15,2);
	VeDauBang(monHocLabel,mhSize,MhLabelNum,XMINTABLE,YDAUBANG);
	y = YTABLE;
	for (i = j; i <j +10 && i < demNode; i++)
	{
		x = XMINTABLE;
		VeDong(mhSize,MhLabelNum,x,y,0);
		InThongTin_MotMonHoc(ds[i]->data,x,y);
		y+=DONG;
	}
	while(1)
	{
		if(kbhit())
		{
			kytu=getch();
			if(kytu==-32) kytu=getch();
			switch (kytu)
			{
				case KEY_UP:
					if(j>=10)
					{
						XoaBangDuLieu();
						j-=10;
						y = YTABLE;
						for (i = j; i <j +10 && i < demNode; i++)
						{
							x = XMINTABLE;
							VeDong(mhSize,MhLabelNum,x,y,0);
							InThongTin_MotMonHoc(ds[i]->data,x,y);
							y+=DONG;
						}
					}
					break;
				case KEY_DOWN:
					if(demNode-j>10)
					{
						XoaBangDuLieu();
						j+=10;
						y = YTABLE;
						for (i = j; i <j +10 && i < demNode; i++)
						{
							x = XMINTABLE;
							VeDong(mhSize,MhLabelNum,x,y,0);
							InThongTin_MotMonHoc(ds[i]->data,x,y);
							y+=DONG;
						}
					}
					break;
				case ESC:
					XoaBang();
					return;
			}
		}
	}
}

void InThongTinMonHoc(MON_HOC *mon,string ThongBao)
{
	XoaBang();
	VeBangThem(ThongBao,monHocLabel,MhLabelNum);
	setbkcolor(15);
	setcolor(0);
	char tam[5];
	outtextxy(XBANGNHAP+10,YBANGNHAP+7,mon->ma_mh);
	outtextxy(XBANGNHAP+10,YBANGNHAP+57,mon->ten_mh);
	outtextxy(XBANGNHAP+10,YBANGNHAP+107,itoa(mon->stc_lt,tam,10));
	outtextxy(XBANGNHAP+10,YBANGNHAP+157,itoa(mon->stc_th,tam,10));
}

MON_HOC *Tim_MonHocTheo_MaMon(TREE &goc,int maMon)
{
	TREE nodeChay=goc;
	int number=0;
	while(nodeChay!=NULL)
	{
		number=atoi(nodeChay->data.ma_mh);
		if(number<0)
			number*=(-1);
		if(number>maMon)
			nodeChay=nodeChay->L;
		else if(number<maMon)
			nodeChay=nodeChay->R;
		else if(number==maMon)
			return &(nodeChay->data); // tim thay
	}
	if(nodeChay==NULL)
		return NULL; // khong tim thay
}

int ChucNangTimMonHoc(TREE &goc,MON_HOC *&mon,string ThongBao) // *& mon == mon, tuc la dang truy cap den dia chi cua mien gia tri cua mon, o day dung *& de bat dau tro den data cua node khi da tim thay trong cay, chi co *& moi thay doi duoc gia tri cua dia chi cua mon,tham chieu den con tro mon de thay doi duoc
{
	XoaBang();
	VeBangNhap(ThongBao,"MA MON HOC");
	char maMon[8];maMon[0]='\0';
	bool check;
	NhapMa(maMon,8,0,XBANGNHAP,YBANGNHAP);
	if(maMon[0]=='\0')	return -1;
	mon=Tim_MonHocTheo_MaMon(goc,atoi(maMon));
	while(mon==NULL)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"MON HOC KHONG TON TAI.", "THONG BAO", MB_OK);
		NhapMa(maMon,8,0,XBANGNHAP,YBANGNHAP);
		if(maMon[0]=='\0')	return -1;
		mon=Tim_MonHocTheo_MaMon(goc,atoi(maMon));
	}
}

int ChucNangLocMonTheoTen(TREE ds[],int &demNode,string ThongBao) // *& mon == mon, tuc la dang truy cap den dia chi cua mien gia tri cua mon, o day dung *& de bat dau tro den data cua node khi da tim thay trong cay, chi co *& moi thay doi duoc gia tri cua dia chi cua mon,tham chieu den con tro mon de thay doi duoc
{
	XoaBang();
	VeBangNhap(ThongBao,"TEN MON HOC");
	char tenMon[52];tenMon[0]='\0';
	Nhap_TenMonHoc(tenMon,52,XBANGNHAP,YBANGNHAP);
	if(tenMon[0]=='\0') return -2;
	unsigned i=0;

	for(i;i<demNode;i++)
	{
		if(strcmp(ds[i]->data.ten_mh,tenMon)==0)
			return i;
	}
	return -1;
}

void XoaMonHocGiaiPhong(TREE &goc, int mamon)
{
	if (goc == NULL) return;
	TREE nodeChay = goc;
	TREE nodeTruoc=NULL;
	int number=0; // node chay
	int number1=0; // node truoc
	while (nodeChay != NULL)
	{
		number=atoi(nodeChay->data.ma_mh);
		number1=atoi(nodeTruoc->data.ma_mh);
		if(number<0)
			number*=(-1);
		if(number1 < 0)
			number1*=(-1);
		if (mamon > number)
		{
			nodeTruoc = nodeChay;
			nodeChay = nodeChay->R;
		}
		else if (mamon < number)
		{
			nodeTruoc = nodeChay;
			nodeChay = nodeChay->L;
		}
		else break;
	}
	if(nodeChay==goc->R) // nodechay co ma = 700000
	{
		number*=(-1);
		itoa(number,nodeChay->data.ma_mh,10);
		return;
	}
	// tim thay r bat dau xoa
	else
	{
		if (nodeChay->L == NULL && nodeChay->R == NULL)// Xoa nut la
		{ 
			if (number > number1) nodeTruoc->R = NULL; // xac dinh node chay o ben nao cua node truoc
			else nodeTruoc->L = NULL;
			delete nodeChay;
			nodeChay=NULL;
		}
		else// Xoa nut co 1 hoac 2 con
		{ 
			if (nodeChay->L == NULL)// Co 1 con ben phai
			{ 
				if(atoi(nodeTruoc->L->data.ma_mh)==number) // de xac dinh node truoc tro trai hay tro phai node can xoa
					nodeTruoc->L=nodeChay->R;
				else  // tuc la nodetruoc ->R(nodeCanxoa) ->nodeCanlien ket lai voi nodetruoc
					nodeTruoc->R=nodeChay->R;
				delete nodeChay;
				nodeChay=NULL;
			}
			else if(nodeChay->R == NULL)// node co con ben trai
			{
				if(atoi(nodeTruoc->R->data.ma_mh)==number)
					nodeTruoc->R=nodeChay->L;
				else 
					nodeTruoc->L=nodeChay->L;
				delete nodeChay;
				nodeChay=NULL;
			}
			else // node 2 con
			{
				TREE node2con=nodeChay; // node o vi tri can phai xoa
				nodeTruoc = nodeChay; // node de lien ket lai sau khi da swap data node can xoa va node thi mang
				nodeChay = nodeChay->R; // la node di tim node the mang
				while (nodeChay->L != NULL)
				{
					nodeTruoc=nodeChay;
					nodeChay = nodeChay->L;
				}
				swapDataMH(node2con->data,nodeChay->data); // swap data node thi mang len vi tri cua node can xoa
				if(atoi(nodeTruoc->data.ma_mh) < atoi(nodeChay->data.ma_mh)) // th nodeChay k co con nao ben trai cung thi lay nodeC thay va lien ket lai
					nodeTruoc->R=nodeChay->R;
				else // node thi mang o ben trai cung ben phai so voi nodeXoa va co hoac k co con ben phai thi lien ket lai
					nodeTruoc->L=nodeChay->R;
				delete nodeChay;
				nodeChay=NULL;
			}
		}
	}
}


int ChucNangSuaMonHoc(DS_LOP_TC dsltc,TREE &goc,MON_HOC *&mon) // *&: dia chi cua mon
{
	MON_HOC tam=*mon;
	int i=0;
	bool check=true;
	for(i;i<dsltc.n_loptc;i++)
	{
		if(atoi(dsltc.ds_ltc[i]->ma_mh)==atoi(mon->ma_mh))
		{
			check=false; // tuc la mon nay da dc mo lop tin chi,cho sua STC thoi
			break;
		}
	}
	if(check) // cho sua them ten mon vi khong co lop nao mo o day
	{
		InThongTinMonHoc(mon,"SUA THONG TIN MON HOC");
		Nhap_TenMonHoc(tam.ten_mh,52,XBANGNHAP,YBANGNHAP+50);
		if(tam.ten_mh[0]=='\0') return -1;
		NhapTinChi(tam.stc_lt,XBANGNHAP,YBANGNHAP+100);
		if(tam.stc_lt==10) return -1;
		NhapTinChi(tam.stc_th,XBANGNHAP,YBANGNHAP+150);
		if(tam.stc_th==10) return -1;
	}
	else // chi sua stc LT va TH vi mon nay da duoc moi lop tc
	{
		InThongTinMonHoc(mon,"SUA THONG TIN MON HOC");
		NhapTinChi(tam.stc_lt,XBANGNHAP,YBANGNHAP+100);
		if(tam.stc_lt==10) return -1;
		NhapTinChi(tam.stc_th,XBANGNHAP,YBANGNHAP+150);
		if(tam.stc_th==10) return -1;
	}
	*mon=tam;
}

int ChucNangXoaMonHoc(DS_LOP_TC &dsltc,TREE &goc,TREE ds[],MON_HOC *&mon,int &demNode,int &viTriMang) 
{
	int maMon=atoi(mon->ma_mh);
	int i=0;
	for(i;i<dsltc.n_loptc;i++)
	{
		if(atoi(dsltc.ds_ltc[i]->ma_mh)==maMon)
		{
			MessageBox(NULL, "CO LOP TIN CHI DUOC MO TU MON HOC NAY,KHONG THE XOA.", "THONG BAO", MB_OK);
			return -1;
		}
	}
	int tam=500000;
	bool check;
	while(tam!=100000)
	{
		if(maMon==tam)
		{
			check=true;
			break;
		}
		else
			tam=((tam-100000)/2)+100000;
	}
	if(tam==100000) check=false; // xoa co giai phong
	int chay=0;
	for(chay;chay<demNode;chay++) // tim vitri de sau khi xoa thi sua tren mang hien thi
	{
		if(atoi(ds[chay]->data.ma_mh)==maMon)
		{
			viTriMang=chay;
			break;
		}
	}
	if(check) // xoa khong giai phong vung nho
	{
		int num=atoi(mon->ma_mh);
		num*=(-1);
		itoa(num,mon->ma_mh,10);
	}
	else
		XoaMonHocGiaiPhong(goc,maMon);
	return 1;
}


void SuaThongTinTrenMang(TREE ds[],int &demNode,int &viTriMang) // xoa tren mang de hien thi
{
	int i=0;
	for(i;i<demNode;i++)
	{
		if(i==viTriMang)
		{
			while(i < demNode)
			{
				ds[i]=ds[i+1];
				i++;
			}
			demNode--;
			return;
		}
	}
}

void SelectMonHoc(DS_LOP_TC &dsltc,TREE &goc)
{
	int demNode=0,chon=0; //chon bien de lam vitri trong mang khi do cay ra mang ddos;
	DemNodeDuong(goc,demNode);   
	if(goc==NULL || demNode ==0)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"DANH SACH MON HOC RONG.", "THONG BAO", MB_OK);
		return;
	}
	TREE ds[demNode]; // de sap xep khong lam thay doi trong cay. dùng mảng TREE đỡ tốn hơn cấp phát động mảng SINH_VIEN
	DoTreeRaMangConTro(goc,ds,chon);
	SapXepMonHocTheo_TenMonHoc(ds,demNode);
	// dung xong thi cho chon =0 de dung lai
	chon=0;
	char kytu;
	short y;
	int GoTo,i,j,viTriMang=0; // i la bien de dem sl con lai de in trang tiep theo ,vitrimang de giu vitri cua phan tu trong mang truoc khi mang di xoa tren cay r quay lai xoa tren mang
	MON_HOC *mon; // tim mon hoc can su ly trong cay
	MonHoc:
//	&(mon)=khoi_taoMH(mon);
	if(demNode==0)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"DANH SACH MON HOC RONG.", "THONG BAO", MB_OK);
		return;
	}
	if(chon==demNode) // xoa cuoi khong in ra 1 dong rac
		chon--;
	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"DANH SACH MON HOC",15,2);
	VeDauBang(monHocLabel,mhSize,MhLabelNum,XMINTABLE,YDAUBANG);
	y = YTABLE;
	for (i = (chon/10)*10; i < ((chon/10)*10)+10 && i < demNode; i++)
	{
		VeDong(mhSize,MhLabelNum,XMINTABLE,y,0);
		InThongTin_MotMonHoc(ds[i]->data,XMINTABLE,y);
		y+=DONG;
	}
	VeDong(mhSize,MhLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
	InThongTin_MotMonHoc(ds[chon]->data,XMINTABLE,YTABLE+((chon%10)*DONG));
	while(1)
	{
		delay(10);
		if(kbhit())
		{
			kytu=getch();
			if(kytu==-32) kytu=getch();
			switch (kytu)
			{
				case KEY_UP:
					if(chon>0)
					{
						if(chon%10==0)
						{
							XoaBangDuLieu();
							chon--;
							y = YTABLE;
							for (i = chon-9; i<= chon; i++)
							{
								VeDong(mhSize,MhLabelNum,XMINTABLE,y,0);
								InThongTin_MotMonHoc(ds[i]->data,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(mhSize,MhLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InThongTin_MotMonHoc(ds[chon]->data,XMINTABLE,YTABLE+((chon%10)*DONG));
							break;
						}
						y = YTABLE;
						VeDong(mhSize,MhLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InThongTin_MotMonHoc(ds[chon]->data,XMINTABLE,YTABLE+((chon%10)*DONG));
						chon--;
						VeDong(mhSize,MhLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InThongTin_MotMonHoc(ds[chon]->data,XMINTABLE,YTABLE+((chon%10)*DONG));
					}
					break;
				case KEY_DOWN:
					if(chon+1 < demNode)
					{
						if((chon+1)%10==0)
						{
							XoaBangDuLieu();
							chon++;
							j=demNode-chon>=10?10:demNode-chon;
							y = YTABLE;
							for (i = chon; i < chon+j; i++)
							{
								VeDong(mhSize,MhLabelNum,XMINTABLE,y,0);
								InThongTin_MotMonHoc(ds[i]->data,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(mhSize,MhLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InThongTin_MotMonHoc(ds[chon]->data,XMINTABLE,YTABLE+((chon%10)*DONG));
							break;
						}
						y = YTABLE;
						VeDong(mhSize,MhLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InThongTin_MotMonHoc(ds[chon]->data,XMINTABLE,YTABLE+((chon%10)*DONG));
						chon++;
						VeDong(mhSize,MhLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InThongTin_MotMonHoc(ds[chon]->data,XMINTABLE,YTABLE+((chon%10)*DONG));
					}
					break;
				case KEY_F1://Tim kiem
				/* tại sao k tìm trên mảng, vì mảng xếp theo tên môn, tìm cây thì nhị phân nhanh hơn. cho 1 con trỏ mon trỏ đến data của node TREE tìm dược
							r thao thác trên data của mon thì data trong node tree cũng thay đổi theo(dùng cho sửa) */
					GoTo=ChucNangTimMonHoc(goc,mon,"TIM KIEM MON HOC");
					if(GoTo==-1)
						goto MonHoc;
					InThongTinMonHoc(mon,"THONG TIN MON HOC");
					while(1)
					{
						if(kbhit())
						{
							kytu=getch();
							if(kytu==-32) kytu=getch();
							switch (kytu)
							{
								case KEY_F2: //sua
									GoTo=ChucNangSuaMonHoc(dsltc,goc,mon);
									if(GoTo==-1)
										goto MonHoc;
									else
										MessageBox(NULL, "SUA THONG TIN MON HOC THANH CONG.", "THONG BAO", MB_OK);
									SapXepMonHocTheo_TenMonHoc(ds,demNode);
									goto MonHoc;
								case KEY_F3: // xoa mom hoc
									GoTo=ChucNangXoaMonHoc(dsltc,goc,ds,mon,demNode,viTriMang);
									if(GoTo==-1)
										goto MonHoc;
									else if(GoTo==1)
										MessageBox(NULL, "XOA MON HOC THANH CONG.", "THONG BAO", MB_OK);
									SuaThongTinTrenMang(ds,demNode,viTriMang);
									goto MonHoc;
								case ESC:
									goto MonHoc;
							}
						}
					}
					break;
				case KEY_F2: // sua
					mon=Tim_MonHocTheo_MaMon(goc,atoi(ds[chon]->data.ma_mh));
					GoTo=ChucNangSuaMonHoc(dsltc,goc,mon);
					if(GoTo==-1)
						goto MonHoc;
					else
						MessageBox(NULL, "SUA THONG TIN MON HOC THANH CONG.", "THONG BAO", MB_OK);
					SapXepMonHocTheo_TenMonHoc(ds,demNode);
					goto MonHoc;
				case KEY_F3://xoa
					mon=Tim_MonHocTheo_MaMon(goc,atoi(ds[chon]->data.ma_mh));
					GoTo=ChucNangXoaMonHoc(dsltc,goc,ds,mon,demNode,viTriMang);
					if(GoTo==-1)
						goto MonHoc;
					else if(GoTo==1)
						MessageBox(NULL, "XOA MON HOC THANH CONG.", "THONG BAO", MB_OK);
					SuaThongTinTrenMang(ds,demNode,viTriMang);
					goto MonHoc;
				case KEY_F4:
					GoTo=ChucNangLocMonTheoTen(ds,demNode,"TIM DANH SACH CAC MON HOC THEO TEN MON");
					if(GoTo==-1)
						goto MonHoc;
					else if(GoTo==-2)
						goto MonHoc;
					else
					{
						chon=GoTo;
						goto MonHoc;
					}
				case ESC:
					XoaBang();
					return;	
			}
		}
	}
}





