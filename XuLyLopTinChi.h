
void disableX(){
	HWND hwnd = NULL;
	
	while (hwnd==NULL)
		hwnd = FindWindow(0,"CHUONG TRINH QUAN LY DIEM SINH VIEN");
	LONG dwStyle=(WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE)&~dwStyle);
}
void setup(){
	HideConsole();
	initwindow(MAXWIDTH, MAXHEIGHT);
	setbkcolor(15);
	cleardevice();

	setwindowtitle("CHUONG TRINH QUAN LY DIEM SINH VIEN");

	settextstyle(0,0,3);
	setcolor(0);
	outtextxy(420,50,"DE TAI QUAN LY DIEM SINH VIEN - NHOM 36");
	outtextxy(600,100,"GVHD: LUU NGUYEN KY THU");
	outtextxy(800,600,"N19DCCN159 - DINH TRUONG SON");
	outtextxy(800,650,"N19DCCN214 - LE THANH TRUNG");
	
	settextstyle(0, 0, 2);
	
	disableX();

	setcolor(0);
	rectangle(MINWIDTHTABLE, MINHEIGHTTABLE, MAXWIDTHTABLE, MAXHEIGHTTABLE);
}

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}
void normal()
{
	setfillstyle(SOLID_FILL, BGCOLOR);
	setbkcolor(BGCOLOR);
	setcolor(0);
}
void highlight()
{
	setfillstyle(SOLID_FILL, 2);
	setbkcolor(2);
	setcolor(15);
}
void normalTable(){
	setcolor(0);
	setbkcolor(15);
	setfillstyle(SOLID_FILL,15);
}
void highlightTable(){
	setcolor(0);
	setbkcolor(3);
	setfillstyle(SOLID_FILL,3);
}
void selectTable(){
	setcolor(0);
	setbkcolor(10);
	setfillstyle(SOLID_FILL,10);
}
void textcenter(short x1, short y1, short x2, short y2, string str, int textcolor, int bgtextcolor)
{
	setbkcolor(bgtextcolor);
	setcolor(textcolor);
	outtextxy((x1 + x2 - (str.length() * FONTSIZE)) / 2, (y1 + y2 - FONTSIZE) / 2, str.c_str());
}
void VeNutMenu(short x, short y, string str)
{
	bar(x, y, x + BUTTONWIDTH, y + BUTTONHEIGHT);
	rectangle(x, y, x + BUTTONWIDTH, y + BUTTONHEIGHT);
	outtextxy((2*x + BUTTONWIDTH - (str.length() * FONTSIZE)) / 2, (2*y + BUTTONHEIGHT - FONTSIZE) / 2, str.c_str());
}
void VeMenu(const string str[], short menuItem)
{
	short x = xMenuChinh, y = yMenuChinh;
	normal();
	for (short i = 0; i < menuItem; i++)
	{
		VeNutMenu(x, y, str[i]);
		y = y + BUTTONHEIGHT + 20;
	}
}
void MenuChinhDong(DS_LOP_TC &dsltc, DS_SV dssv, TREE &dsmh, short chon)
{
	setcolor(0);
	rectangle(xMenuChinh,320,260,MAXHEIGHTTABLE-10);
	textcenter(xMenuChinh+5,350,260,350,"HUONG DAN",15,1);

	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,380,"ENTER: CHON");
	outtextxy(xMenuChinh+5,410,"ESC: QUAY LAI");
	outtextxy(xMenuChinh+5,440, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,470, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,500, "DI CHUYEN");

	VeMenu(menuChinh, menuChinhItem);	
	highlight();
	VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuChinh[chon]);
	char kytu;
	do
	{
		delay(10);
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu)
		{
			case KEY_UP:
				if (chon > 0)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuChinh[chon]);
					chon--;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuChinh[chon]);
				}
				break;
			case KEY_DOWN:
				if (chon + 1 < menuChinhItem)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuChinh[chon]);
					chon++;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuChinh[chon]);
				}
				break;
			case ENTER:
			{
				XoaMenu();
				if (chon == 0){
					MenuLtcDong(dsltc,dssv,dsmh,0);
					return MenuChinhDong(dsltc,dssv,dsmh,chon);
				} 
				else if (chon == 1){
					MenuSvDong(dsltc,dssv,dsmh,0);
					return MenuChinhDong(dsltc,dssv,dsmh,chon);
				} 
				else if (chon == 2){
					MenuMhDong(dsltc,dsmh,0);
					return MenuChinhDong(dsltc,dssv,dsmh,chon);
				} 
				else if (chon == 3){
					MenuDiemDong(dsltc,dssv,dsmh,0);
					return MenuChinhDong(dsltc,dssv,dsmh,chon);
				} 
				break;
			}
			case ESC:
				short a = MessageBox(NULL, "BAN MUON THOAT CHUONG TRINH?", "THONG BAO", MB_YESNO);
				if (a == 6){
					// Giai phong bo nho va luu file
					GhiFileLopTinChi(dsltc);
					Ghi_FILE_DSSV(dssv);
					Ghi_FILE_MonHoc(dsmh);
					GiaiPhongDSLTC(dsltc);
					exit(0);
				}
				break;
		}
	} while (1);
}
void MenuLtcDong(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh, short chon){

	XoaBang();
	XoaHDSD();
	VeMenu(menuLopTinChi, menuLtcItem);
	highlight();
	VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuLopTinChi[chon]);

	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,440, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,470, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,500, "DI CHUYEN");

	char kytu;
	do
	{
		delay(10);
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu)
		{
			case KEY_UP:
				if (chon > 0)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuLopTinChi[chon]);
					chon--;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuLopTinChi[chon]);
				}
				break;
			case KEY_DOWN:
				if (chon + 1 < menuLtcItem)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuLopTinChi[chon]);
					chon++;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuLopTinChi[chon]);
				}
				break;
			case ENTER:
			{
				if (chon == 0){
					XoaHDSD();
					ThemLopTinChi(ds,dsmh);
					return MenuLtcDong(ds,dssv,dsmh,chon);
				} 
				else if (chon == 1){
					XoaHDSD();
					SelectLopTinChi(ds,dssv,dsmh);
					return MenuLtcDong(ds,dssv,dsmh,chon);
				} 
				else if (chon == 2){
					if (ds.n_loptc == 0){
						MessageBeep(0xFFFFFFFF);
						MessageBox(NULL,"KHONG CO LOP TIN CHI NAO TRONG DANH SACH.", "THONG BAO", MB_OK);
						// return MenuLtcDong(ds,dssv,dsmh,chon);
						break;
					}
					XoaHDSD();
					AutoHuyLopTinChi(ds);
					return MenuLtcDong(ds,dssv,dsmh,chon);
				}
				else if (chon == 3){
					XoaHDSD();
					InDsdkLopTinChi(ds,dssv,dsmh);
					return MenuLtcDong(ds,dssv,dsmh,chon);
				}
			}
			case ESC: return;
		}
	} while (1);
}
void MenuSvDong(DS_LOP_TC &dsltc, DS_SV &dssv, TREE dsmh, short chon){
	XoaBang();
	XoaHDSD();
	VeMenu(menuSinhVien, menuSinhVienItem);
	highlight();
	VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuSinhVien[chon]);

	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,440, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,470, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,500, "DI CHUYEN");

	char kytu;
	do
	{
		delay(10);
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu)
		{
			case KEY_UP:
				if (chon > 0)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuSinhVien[chon]);
					chon--;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuSinhVien[chon]);
				}
				break;
			case KEY_DOWN:
				if (chon + 1 < menuSinhVienItem)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuSinhVien[chon]);
					chon++;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuSinhVien[chon]);
				}
				break;
			case ENTER:
			{
				if (chon == 0){
					XoaHDSD();
					Chuc_Nang_Them_SV_Theo_LOP(dssv);
					return MenuSvDong(dsltc,dssv,dsmh,chon);
				}
				else if (chon == 1){
					XoaHDSD();
					SelectSV(dsltc,dssv);
					return MenuSvDong(dsltc,dssv,dsmh,chon);
				}
				else if (chon == 2){
					XoaHDSD();
					DangKyLopTinChi(dsltc,dssv,dsmh);
					return MenuSvDong(dsltc,dssv,dsmh,chon);
				}
				else if (chon == 3){
					XoaHDSD();
					in_DsLopSV(dssv);
					return MenuSvDong(dsltc,dssv,dsmh,chon);
				}
			}
			case ESC: return;
		}
	} while (1);
}
void MenuMhDong(DS_LOP_TC &dsltc, TREE &dsmh, short chon){
	XoaBang();
	XoaHDSD();
	VeMenu(menuMonHoc, menuMonHocItem);
	highlight();
	VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuMonHoc[chon]);

	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,440, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,470, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,500, "DI CHUYEN");
	// doc file chieu cao , tong node va so node da xoa
	int chieuCao=1;
	int tongNode=0;
	Doc_FILE_Num(chieuCao,tongNode);
	MenuMh:
	XoaBang();
	char kytu;
	do
	{
		delay(10);
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu)
		{
			case KEY_UP:
				if (chon > 0)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuMonHoc[chon]);
					chon--;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuMonHoc[chon]);
				}
				break;
			case KEY_DOWN:
				if (chon + 1 < menuMonHocItem)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuMonHoc[chon]);
					chon++;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuMonHoc[chon]);
				}
				break;
			case ENTER:
			{
				if (chon == 0){
					XoaHDSD();
					ChucNang_ThemMonHoc(dsmh,chieuCao,tongNode);
					// return MenuMhDong(dsltc,dsmh,chon);
					goto MenuMh;
				}
				else if (chon == 1){
					SelectMonHoc(dsltc,dsmh);
					// return MenuMhDong(dsltc,dsmh,chon);
					goto MenuMh;
				}
				else if (chon == 2){
					XoaHDSD();
					In_DsMonHoc(dsmh);
					// return MenuMhDong(dsltc,dsmh,chon);
					goto MenuMh;
				}
			}
			case ESC: 
			{
				Ghi_FILE_num(chieuCao,tongNode);
				Ghi_FILE_MonHoc(dsmh);
				return; //ghi file
			}
		}
	} while (1);
}
void MenuDiemDong(DS_LOP_TC &dsltc, DS_SV dssv, TREE dsmh, short chon){
	XoaBang();
	XoaHDSD();
	VeMenu(menuDiem, menuDiemItem);
	highlight();
	VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuDiem[chon]);

	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,440, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,470, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,500, "DI CHUYEN");

	QuickSortTheoTenMon(dsltc,dsmh,0,dsltc.n_loptc-1);

	char kytu;
	do
	{
		delay(10);
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu)
		{
			case KEY_UP:
				if (chon > 0)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuDiem[chon]);
					chon--;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuDiem[chon]);
				}
				break;
			case KEY_DOWN:
				if (chon + 1 < menuDiemItem)
				{
					normal();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuDiem[chon]);
					chon++;
					highlight();
					VeNutMenu(xMenuChinh, yMenuChinh + chon * 80, menuDiem[chon]);
				}
				break;
			case ENTER:
			{
				if (chon == 0){
					XoaHDSD();
					ChucNangNhapDiem(dsltc,dssv,dsmh);
					return MenuDiemDong(dsltc,dssv,dsmh,chon);
				}
				else if (chon == 1){
					XoaHDSD();
					InDiemLopTinChi(dsltc,dssv,dsmh);
					return MenuDiemDong(dsltc,dssv,dsmh,chon);
				}
				else if (chon == 2){
					XoaHDSD();
					InDiemTrungBinh(dsltc,dssv,dsmh);
					return MenuDiemDong(dsltc,dssv,dsmh,chon);
				}
			}
			case ESC: return;
		}
	} while (1);
}
void XoaMenu()
{
	setfillstyle(SOLID_FILL, BGCOLOR);
	bar(xMenuChinh,yMenuChinh,xMenuChinh+BUTTONWIDTH+5,YMAXMENU);
}
void XoaBang()
{
	setfillstyle(SOLID_FILL, BGCOLOR);
	bar(xMenuChinh+BUTTONWIDTH+5,yMenuChinh+5,MAXWIDTHTABLE-5,MAXHEIGHTTABLE-5);
}
void XoaBangDuLieu(){
	setfillstyle(SOLID_FILL, BGCOLOR);
	bar(xMenuChinh+BUTTONWIDTH+5,YTABLE,MAXWIDTHTABLE-5,MAXHEIGHTTABLE-5);
}
void XoaHDSD(){
	setfillstyle(SOLID_FILL,15);
	bar(xMenuChinh+3,440,xMenuChinh+BUTTONWIDTH-5,MAXHEIGHTTABLE-15);
}
void VeBangThem(string main, const string *label, short soLuong)
{
	short x1=XMINBANGTHEM,y1=YMINBANGTHEM,x2=XMAXBANGTHEM,y2=soLuong*50+YBANGNHAP;
	setcolor(3);
	setlinestyle(SOLID_LINE,1,5);
	rectangle(x1,y1,x2,y2);
	setbkcolor(2);
	textcenter(x1,y1,x2,y1+40,main,15,2);
	x1 += 10;
	y1 += 60;
	setlinestyle(SOLID_LINE,1,1);
	for (short i = 0; i < soLuong; i++){
		tao_label(x1,y1,x1+200,y1+30,9,0,label[i]);
		tao_input(x1+200,y1,x2-10,y1+30);
		y1 += 50;
	}
}
void VeBangNhap(string main, string label){
	short x1 = XMINBANGTHEM, y1 = YMINBANGTHEM, x2 = XMAXBANGTHEM, y2 = YMAXBANGTIMKIEM;
	setcolor(3);
	setlinestyle(SOLID_LINE,1,5);
	rectangle(x1,y1,x2,y2);
	setbkcolor(2);
	textcenter(x1,y1,x2,y1 + 40,main,15,2);
	x1 += 10;
	y1 += 60;
	setlinestyle(SOLID_LINE,1,1);
	tao_label(x1,y1,x1+200,y1+30,9,0,label);
	tao_input(x1+200,y1,x2-10,y1+30);
}
void tao_label(int x1, int y1, int x2, int y2, int mau_nen, int mau_chu, string label){
	setcolor(mau_chu);
	setbkcolor(mau_nen);
	setfillstyle(SOLID_FILL, mau_nen);
	bar(x1,y1,x2,y2);
	outtextxy(x1 + 5, (y2 + y1 - FONTSIZE) / 2, label.c_str());
}
void tao_input(int x1, int y1, int x2, int y2){
	setfillstyle(SOLID_FILL, 15);
	setcolor(0);
	bar(x1,y1,x2,y2);
	rectangle(x1,y1,x2,y2);
}
void xoa_input(int x1, int y1){
	setfillstyle(SOLID_FILL,15);
	setcolor(0);
	bar(x1,y1,XMAXBANGTHEM-10,y1+30);
	rectangle(x1,y1,XMAXBANGTHEM-10,y1+30);
}
void XoaDiem(short y){
	setfillstyle(SOLID_FILL,15);
	setcolor(0);
	bar(XNHAPDIEM,y,XMAXNHAPDIEM,y+DONG);
	rectangle(XNHAPDIEM,y,XMAXNHAPDIEM,y+DONG);
}
void VeDauBang(const string *title, const short *doRongCot, short soLuongCot, short x, short y){
	setcolor(0);
	for (short i = 0; i < soLuongCot; i++){
		rectangle(x,y,x+doRongCot[i],y+DONG);
		textcenter(x,y,x+doRongCot[i],y+DONG,title[i],0,15);
		x += doRongCot[i];
	}
}
void VeDong(const short *doRongCot, short soLuongCot, short x, short y, short highlight){
	
	if (highlight == 0){ // khong highlight
		normalTable();
		for (short i = 0; i < soLuongCot; i++){
			bar(x,y,x+doRongCot[i],y+DONG);
			rectangle(x,y,x+doRongCot[i],y+DONG);
			x += doRongCot[i];
		}
	}
	else if (highlight == 1){ // da dang ky
		highlightTable();
		for (short i = 0; i < soLuongCot; i++){
			bar(x,y,x+doRongCot[i],y+DONG);
			rectangle(x,y,x+doRongCot[i],y+DONG);
			x += doRongCot[i];
		}
	}
	else{ // highlight
		selectTable();
		for (short i = 0; i < soLuongCot; i++){
			bar(x,y,x+doRongCot[i],y+DONG);
			rectangle(x,y,x+doRongCot[i],y+DONG);
			x += doRongCot[i];
		}
	}
}
void InLtcTheoDong(LOP_TC *lop, short stt, short x, short y){
	char tam[10];
	outtextxy(x+5,y+12,itoa(stt,tam,10));
	x+=TABLELTCSIZE2[0]; outtextxy(x+5,y+12,itoa(lop->ma_lop_tc, tam, 10));
	x+=TABLELTCSIZE2[1]; outtextxy(x+5,y+12,lop->ma_mh);
	x+=TABLELTCSIZE2[2]; outtextxy(x+5,y+12,itoa(lop->khoa, tam, 10));
	x+=TABLELTCSIZE2[3]; outtextxy(x+5,y+12,itoa(lop->hoc_ky, tam, 10));
	x+=TABLELTCSIZE2[4]; outtextxy(x+5,y+12,itoa(lop->nhom, tam, 10));
	x+=TABLELTCSIZE2[5]; outtextxy(x+5,y+12,itoa(lop->sv_min, tam, 10));
	x+=TABLELTCSIZE2[6]; outtextxy(x+5,y+12,itoa(lop->sv_max, tam, 10));
	x+=TABLELTCSIZE2[7];
	if (lop->trang_thai) outtextxy(x+5,y+12,"MO");
	else outtextxy(x+5,y+12,"HUY");
}
void InLtcTheoDong(LOP_TC* lop, TREE dsmh, short x, short y){
	char tam[10];
	char a[2];
	outtextxy(x+5,y+12,itoa(lop->ma_lop_tc, tam, 10));
	x+=TABLELTCSIZE[0]; outtextxy(x+5,y+12,lop->ma_mh);
	x+=TABLELTCSIZE[1];
	outtextxy(x+5,y+12,Tim_MonHocTheo_MaMon(dsmh,atoi(lop->ma_mh))->ten_mh);
	itoa(lop->khoa,tam,10); strcat(tam,"/");
	itoa(lop->hoc_ky,a,10); strcat(tam, a);
	x+=TABLELTCSIZE[2]; outtextxy(x+5,y+12,tam);
	x+=TABLELTCSIZE[3]; outtextxy(x+5,y+12,itoa(lop->nhom, tam, 10));
}
void InDsdkTheoDong(DS_SV dssv, char* ma, short stt, short x, short y){
	char tam[10];
	outtextxy(x+5,y+12,itoa(stt,tam,10));
	x+=TABLEDKSIZE[0]; outtextxy(x+5,y+12,ma);
	DS_SV nodeTam = Check_maSV_TrongDSSV1(dssv,ma);
	x+=TABLEDKSIZE[1]; outtextxy(x+5,y+12,nodeTam->data.ho);
	x+=TABLEDKSIZE[2]; outtextxy(x+5,y+12,nodeTam->data.ten);
	x+=TABLEDKSIZE[3]; outtextxy(x+5,y+12,nodeTam->data.gioi_tinh);
	x+=TABLEDKSIZE[4]; outtextxy(x+5,y+12,nodeTam->data.sdt);
	x+=TABLEDKSIZE[5]; outtextxy(x+5,y+12,nodeTam->data.ma_lop_sv);
}
void InDangKyMonTheoDong(LOP_TC *lop, TREE dsmh, short sl, short x, short y){
	char tam[5];
	outtextxy(x+5,y+12,lop->ma_mh);
	x+= dkmSize[0]; outtextxy(x+5,y+12,Tim_MonHocTheo_MaMon(dsmh,atoi(lop->ma_mh))->ten_mh);
	x+= dkmSize[1]; outtextxy(x+5,y+12,itoa(lop->nhom,tam,10));
	x+= dkmSize[2]; outtextxy(x+5,y+12,itoa(sl,tam,10));
	x+= dkmSize[3]; outtextxy(x+5,y+12,itoa(lop->sv_max-sl,tam,10));
}
void SelectMonHoc(){
	textcenter(XMINTABLE,10,XMAXTABLE,YDAUBANG,"DANH SACH MON HOC",15,2);
}
void SelectLopTinChi(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh){
	if (ds.n_loptc == 0){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "KHONG CO LOP TIN CHI NAO TRONG DANH SACH.", "THONG BAO", MB_OK);
		return;
	}

	QuickSortTheoTenMon(ds,dsmh,0,ds.n_loptc-1);

	short y;
	short a;
	char kytu;
	short chon = 0;

	loop:
	XoaHDSD();
	setfillstyle(SOLID_FILL,3);
	bar(20,440,50,456);
	setcolor(0);
	setbkcolor(15);
	outtextxy(55,440,": LOP DA MO");
	outtextxy(xMenuChinh+5,470,"F1: TIM KIEM");
	outtextxy(xMenuChinh+5,500,"F2: SUA LOP");
	outtextxy(xMenuChinh+5,530,"F3: XOA LOP");
	outtextxy(xMenuChinh+5,560, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,590, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,620, "DI CHUYEN");

	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"DANH SACH LOP TIN CHI",15,2);
	VeDauBang(TABLELTC,TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YDAUBANG);
	y = YTABLE;
	for (short j = (chon/10)*10; j < ((chon/10)*10)+10 && j < ds.n_loptc; j++){
		if (ds.ds_ltc[j]->trang_thai) VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,1);
		else VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
		InLtcTheoDong(ds.ds_ltc[j],dsmh,XMINTABLE,y);
		y+=DONG;
	}
	
	VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
	InLtcTheoDong(ds.ds_ltc[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));

	while (1){
		delay(10);
		if (kbhit()){
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu){
				case KEY_UP:
					if (chon > 0){
						if (chon % 10 == 0)
						{
							XoaBangDuLieu();
							chon--;
							y = YTABLE;
							for (short j = chon-9; j <= chon; j++)
							{
								if (ds.ds_ltc[j]->trang_thai) VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,1);
								else VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
								InLtcTheoDong(ds.ds_ltc[j],dsmh,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLtcTheoDong(ds.ds_ltc[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						if (ds.ds_ltc[chon]->trang_thai) VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),1);
						else VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLtcTheoDong(ds.ds_ltc[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon--;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLtcTheoDong(ds.ds_ltc[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case KEY_DOWN:
					if (chon + 1 < ds.n_loptc){
						if ((chon + 1) % 10 == 0)
						{
							XoaBangDuLieu();
							chon++;
							short conlai = ds.n_loptc - chon >= 10 ? 10 : ds.n_loptc - chon;
							y = YTABLE;
							for (short j = chon; j < chon + conlai; j++)
							{
								if (ds.ds_ltc[j]->trang_thai) VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,1);
								else VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
								InLtcTheoDong(ds.ds_ltc[j],dsmh,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLtcTheoDong(ds.ds_ltc[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						if (ds.ds_ltc[chon]->trang_thai) VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),1);
						else VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLtcTheoDong(ds.ds_ltc[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon++;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLtcTheoDong(ds.ds_ltc[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case KEY_F1:{ // CHUC NANG TIM KIEM
					XoaBang();
					VeBangNhap("TIM KIEM LOP TIN CHI", "MA LOP TC");
					char malop[8]; malop[0] = '\0';
					NhapMa(malop,7,0,XBANGNHAP,YBANGNHAP);
					if (malop[0] == '\0') goto loop;
					short tim = TimKiemLopTinChi(ds,atoi(malop));
					while (tim == -1){
						MessageBeep(0xFFFFFFFF);
						MessageBox(NULL,"LOP KHONG TON TAI.", "THONG BAO", MB_OK);
						NhapMa(malop,7,0,XBANGNHAP,YBANGNHAP);
						if (malop[0] == '\0') goto loop;
						tim = TimKiemLopTinChi(ds,atoi(malop));
					}
					setcolor(0);
					setbkcolor(15);
					XoaHDSD();
					outtextxy(xMenuChinh+5,440,"F2: SUA LOP");
					outtextxy(xMenuChinh+5,470,"F3: XOA LOP");

					InThongTinLTC(ds.ds_ltc[tim]);
					xem:
					while (1){
						delay(10);
						if (kbhit()){
							kytu = getch();
							if (kytu == -32) kytu = getch();
							switch(kytu){
								case KEY_F2:{
									if (ds.ds_ltc[tim]->ds_svdk == NULL){ // NEU CHUA CO SV DANG KY -> CHO SUA
										SuaLopTinChi(ds,dsmh,tim);
										goto loop;
									}
									else{ // NEU CO SV DANG KY
										if (ds.ds_ltc[tim]->trang_thai){ // LOP DA MO
											MessageBeep(0xFFFFFFFF);
											MessageBox(NULL, "LOP DA MO. KHONG THE SUA.", "THONG BAO", MB_OK);
										}
										else{ // LOP CHUA MO
												SuaLopTinChi(ds,dsmh,tim);
												goto loop;
											}
										}
									}
									goto xem;
								case KEY_F3:{
									if (ds.ds_ltc[tim]->trang_thai){
										if (KiemTraDaCoDiem(ds.ds_ltc[tim])){
											a = MessageBox(NULL, "LOP DA CO DIEM. BAN CO CHAC CHAN MUON XOA?", "THONG BAO", MB_YESNO);
											if (a == 6){
												XoaLopTinChi(ds,tim); // a = 6 -> YES
												if (ds.n_loptc == 0) return;
												chon = 0;
												goto loop;
											}
										}
										else{
											MessageBeep(0xFFFFFFFF);
											MessageBox(NULL, "LOP DANG HOC. KHONG THE XOA.", "THONG BAO", MB_OK);
										}
									}
									else{
										if (ds.ds_ltc[tim]->ds_svdk != NULL){
											a = MessageBox(NULL, "LOP DA CO SINH VIEN DANG KY.\nBAN CO CHAC CHAN MUON XOA?", "THONG BAO", MB_YESNO);
											if (a == 6){
												XoaLopTinChi(ds,tim); // a = 6 -> YES
												if (ds.n_loptc == 0) return;
												chon = 0;
												goto loop;
											}
										}
										else{
											a = MessageBox(NULL, "BAN CO CHAC CHAN MUON XOA?", "THONG BAO", MB_YESNO);
											if (a == 6){
												XoaLopTinChi(ds,tim);
												if (ds.n_loptc == 0) return;
												chon = 0;
												goto loop;
											}
										}
									}
									break;
								}
								case ESC: goto loop;
							}
						}
					}
				}
				case KEY_F2:
					if (ds.ds_ltc[chon]->ds_svdk == NULL){ // NEU CHUA CO SV DANG KY -> CHO SUA
						SuaLopTinChi(ds,dsmh,chon);
						goto loop;
					}
					else{ // NEU CO SV DANG KY
						if (ds.ds_ltc[chon]->trang_thai){ // LOP DA MO
							MessageBeep(0xFFFFFFFF);
							MessageBox(NULL, "LOP DA MO. KHONG THE SUA.", "THONG BAO", MB_OK);
						}
						else{ // LOP CHUA MO
							SuaLopTinChi(ds,dsmh,chon);
							goto loop;
						}
					}
					break;
				case KEY_F3:
					if (ds.ds_ltc[chon]->trang_thai){
						if (KiemTraDaCoDiem(ds.ds_ltc[chon])){
							a = MessageBox(NULL, "LOP DA CO DIEM. BAN CO CHAC CHAN MUON XOA?", "THONG BAO", MB_YESNO);
							if (a == 6){
								XoaLopTinChi(ds,chon); // a = 6 -> YES
								if (ds.n_loptc == 0) return;
								chon = 0;
								goto loop;
							}
						}
						else{
							MessageBeep(0xFFFFFFFF);
							MessageBox(NULL, "LOP DANG HOC. KHONG THE XOA.", "THONG BAO", MB_OK);
						}
					}
					else{
						if (ds.ds_ltc[chon]->ds_svdk != NULL){
							a = MessageBox(NULL, "LOP DA CO SINH VIEN DANG KY.\nBAN CO CHAC CHAN MUON XOA?", "THONG BAO", MB_YESNO);
							if (a == 6){
								XoaLopTinChi(ds,chon); // a = 6 -> YES
								if (ds.n_loptc == 0) return;
								chon = 0;
								goto loop;
							}
						}
						else{
							a = MessageBox(NULL, "BAN CO CHAC CHAN MUON XOA?", "THONG BAO", MB_YESNO);
							if (a == 6){
								XoaLopTinChi(ds,chon);
								if (ds.n_loptc == 0) return;
								chon = 0;
								goto loop;
							}
						}
					}
					break;
				case ENTER:
					setcolor(0);
					setbkcolor(15);
					XoaHDSD();
					outtextxy(xMenuChinh+5,440,"F2: SUA LOP");
					outtextxy(xMenuChinh+5,470,"F3: XOA LOP");

					InThongTinLTC(ds.ds_ltc[chon]);
					
					while (1){
						delay(10);
						if (kbhit()){
							kytu = getch();
							if (kytu == -32) kytu = getch();
							switch(kytu){
								case KEY_F2:
									if (ds.ds_ltc[chon]->ds_svdk == NULL){ // NEU CHUA CO SV DANG KY -> CHO SUA
										SuaLopTinChi(ds,dsmh,chon);
										goto loop;
									}
									else{ // NEU CO SV DANG KY
										if (ds.ds_ltc[chon]->trang_thai){ // LOP DA MO
											MessageBeep(0xFFFFFFFF);
											MessageBox(NULL, "LOP DA MO. KHONG THE SUA.", "THONG BAO", MB_OK);
										}
										else{ // LOP CHUA MO
											SuaLopTinChi(ds,dsmh,chon);
											goto loop;
										} 
									}
									break;
								case KEY_F3:
									if (ds.ds_ltc[chon]->trang_thai){
										if (KiemTraDaCoDiem(ds.ds_ltc[chon])){
											a = MessageBox(NULL, "LOP DA CO DIEM. BAN CO CHAC CHAN MUON XOA?", "THONG BAO", MB_YESNO);
											if (a == 6){
												XoaLopTinChi(ds,chon); // a = 6 -> YES
												if (ds.n_loptc == 0) return;
												chon = 0;
												goto loop;
											}
										}
										else{
											MessageBeep(0xFFFFFFFF);
											MessageBox(NULL, "LOP DANG HOC. KHONG THE XOA.", "THONG BAO", MB_OK);
										}
									}
									else{
										if (ds.ds_ltc[chon]->ds_svdk != NULL){
											a = MessageBox(NULL, "LOP DA CO SINH VIEN DANG KY.\nBAN CO CHAC CHAN MUON XOA?", "THONG BAO", MB_YESNO);
											if (a == 6){
												XoaLopTinChi(ds,chon); // a = 6 -> YES
												if (ds.n_loptc == 0) return;
												chon = 0;
												goto loop;
											}
										}
										else{
											a = MessageBox(NULL, "BAN CO CHAC CHAN MUON XOA?", "THONG BAO", MB_YESNO);
											if (a == 6){
												XoaLopTinChi(ds,chon);
												if (ds.n_loptc == 0) return;
												chon = 0;
												goto loop;
											}
										}
									}
									break;
								case ESC: goto loop;
							}
						}
					}
				case ESC: return;
			}
		}
	}
}
void InDsdkLopTinChi(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh){
	short sl = 0;
	short chon = 0;
	short tam = 0;
	short y;
	short a;
	char kytu;

	for (short i = 0; i < ds.n_loptc; i++)
		if (ds.ds_ltc[i]->ds_svdk != NULL) sl++;

	if (sl == 0){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "KHONG CO LOP TIN CHI NAO CO SINH VIEN DANG KY.", "THONG BAO", MB_OK);
		return;
	}

	LOP_TC* dslop[sl];

	for (short i = 0; i < ds.n_loptc; i++)
		if (ds.ds_ltc[i]->ds_svdk != NULL) dslop[tam++] = ds.ds_ltc[i];

	loop:
	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"DANH SACH DANG KY LOP TIN CHI",15,2);
	VeDauBang(TABLELTC,TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YDAUBANG);
	
	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,440,"F1: TIM KIEM");
	outtextxy(xMenuChinh+5,470, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,500, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,530, "DI CHUYEN");

	y = YTABLE;
	for (short j = (chon/10)*10; j < ((chon/10)*10)+10 && j < sl; j++){
		VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
		// InLtcTheoDong(dslop[j],j+1,XMINTABLE,y);
		InLtcTheoDong(dslop[j],dsmh,XMINTABLE,y);
		y+=DONG;
	}
	
	VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
	// InLtcTheoDong(dslop[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
	InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
	
	while (1){
		delay(10);
		if (kbhit()){
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu){
				case KEY_UP:
					if (chon > 0){
						if (chon % 10 == 0)
						{
							XoaBangDuLieu();
							chon--;
							y = YTABLE;
							for (short j = chon-9; j <= chon; j++)
							{
								VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
								// InLtcTheoDong(dslop[j],j+1,XMINTABLE,y);
								InLtcTheoDong(dslop[j],dsmh,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							// InLtcTheoDong(dslop[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
							InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						// InLtcTheoDong(dslop[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
						InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon--;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						// InLtcTheoDong(dslop[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
						InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case KEY_DOWN:
					if (chon + 1 < sl){
						if ((chon + 1) % 10 == 0)
						{
							XoaBangDuLieu();
							chon++;
							short conlai = sl - chon >= 10 ? 10 : sl - chon;
							y = YTABLE;
							for (short j = chon; j < chon + conlai; j++)
							{
								VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
								// InLtcTheoDong(dslop[j],j+1,XMINTABLE,y);
								InLtcTheoDong(dslop[j],dsmh,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							// InLtcTheoDong(dslop[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
							InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						// InLtcTheoDong(dslop[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
						InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon++;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						// InLtcTheoDong(dslop[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
						InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case KEY_F1:{ // CHUC NANG TIM KIEM
					XoaBang();
					VeBangNhap("TIM KIEM LOP TIN CHI", "MA LOP TC");
					char malop[8]; malop[0] = '\0';
					NhapMa(malop,7,0,XBANGNHAP,YBANGNHAP);
					if (malop[0] == '\0') goto loop;
					short tim = TimKiemLopTinChi(dslop,sl,atoi(malop));
					while (tim == -1){
						MessageBeep(0xFFFFFFFF);
						MessageBox(NULL,"LOP KHONG CO SINH VIEN DANG KY HOAC KHONG TON TAI.", "THONG BAO", MB_OK);
						NhapMa(malop,7,0,XBANGNHAP,YBANGNHAP);
						if (malop[0] == '\0') goto loop;
						tim = TimKiemLopTinChi(dslop,sl,atoi(malop));
					}
					InDanhSachDangKy(dslop[tim],dssv);
					goto loop;
				}
				case ENTER:
					InDanhSachDangKy(dslop[chon],dssv);
					goto loop;
				case ESC: return;
			}
		}
	}
}
void InDiemLopTinChi(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh){
	short sl = 0;
	short tam = 0;
	short chon = 0;
	char kytu;

	for (short i = 0; i < ds.n_loptc; i++)
		if (ds.ds_ltc[i]->trang_thai) sl++;

	if (sl == 0){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "CHUA CO LOP NAO CO DIEM.", "THONG BAO", MB_OK);
		return;
	}

	LOP_TC* dslop[sl];

	for (short i = 0; i < ds.n_loptc; i++)
		if (ds.ds_ltc[i]->trang_thai)
			dslop[tam++] = ds.ds_ltc[i];

	loop:
	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"BANG DIEM LOP TIN CHI",15,2);
	VeDauBang(TABLELTC,TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YDAUBANG);
	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,440, "F1: TIM KIEM");
	outtextxy(xMenuChinh+5,470, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,500, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,530, "DI CHUYEN");	

	short y = YTABLE;
	for (short j = (chon/10)*10; j < ((chon/10)*10)+10 && j < sl; j++){
		VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
		InLtcTheoDong(dslop[j],dsmh,XMINTABLE,y);
		y+=DONG;
	}
	
	VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
	InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
	
	while (1){
		delay(10);
		if (kbhit()){
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu){
				case KEY_UP:
					if (chon > 0){
						if (chon % 10 == 0)
						{
							XoaBangDuLieu();
							chon--;
							y = YTABLE;
							for (short j = chon-9; j <= chon; j++)
							{
								VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
								InLtcTheoDong(dslop[j],dsmh,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon--;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case KEY_DOWN:
					if (chon + 1 < sl){
						if ((chon + 1) % 10 == 0)
						{
							XoaBangDuLieu();
							chon++;
							short conlai = sl - chon >= 10 ? 10 : sl - chon;
							y = YTABLE;
							for (short j = chon; j < chon + conlai; j++)
							{
								VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
								InLtcTheoDong(dslop[j],dsmh,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon++;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLtcTheoDong(dslop[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case KEY_F1:{
					XoaBang();
					string label[4] = {"NIEN KHOA", "HOC KY", "NHOM", "MA MON"};
					

					unsigned short nk,hk,nhom;
					char tam[4]; 
					char* mamon;
					short i;

					nhaplai:
					VeBangThem("TIM KIEM LOP TIN CHI",label,4);
					tam[0] = '\0';
					nk=hk=nhom=0;

					xoa_input(XBANGNHAP,YBANGNHAP);
					NhapNienKhoa(nk,XBANGNHAP,YBANGNHAP);
					if (nk == 0) goto loop;

					xoa_input(XBANGNHAP,YBANGNHAP+50);
					NhapHocKy(hk,XBANGNHAP,YBANGNHAP+50);
					if (hk == 0) goto loop;

					xoa_input(XBANGNHAP,YBANGNHAP+100);
					NhapMa(tam,4,0,XBANGNHAP,YBANGNHAP+100); // Nhom
					nhom = atoi(tam);
					while (nhom == 0){
						if (tam[0] == '\0') return;
						MessageBeep(0xFFFFFFFF);
						MessageBox(NULL,"NHOM PHAI KHAC 0.", "THONG BAO", MB_OK);
						xoa_input(XBANGNHAP,YBANGNHAP+100);
						tam[0] = '\0';
						NhapMa(tam,4,0,XBANGNHAP,YBANGNHAP+100);
					}

					mamon = ChonMonHoc(dsmh);
					if (mamon == NULL) return;

					for (i = 0; i < sl; i++){
						if (KiemTraTrungChuoi(dslop[i]->ma_mh,mamon) && dslop[i]->khoa == nk && dslop[i]->hoc_ky == hk && dslop[i]->nhom == nhom){
							InDiem(dslop[i],dssv,dsmh);
							goto loop;
						}
					}
					MessageBeep(0xFFFFFFFF);
					MessageBoxA(NULL, "LOP DANG TRONG TRANG THAI HUY HOAC KHONG TON TAI.", "THONG BAO", MB_OK);
					goto nhaplai;
					
				}
				case ENTER:
					InDiem(dslop[chon],dssv,dsmh);
					goto loop;
				case ESC: return;
			}
		}
	}
}
void InDiemTrungBinh(DS_LOP_TC ds, DS_SV dssv, TREE dsmh){
	if(dssv==NULL){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"KHONG CO LOP NAO.", "THONG BAO", MB_OK);
		return;
    }
	
    unsigned int dem = 1;
	unsigned int demSV=1;
    unsigned int viTri=1;

	QuickSortTichHop(ds,0,ds.n_loptc-1);

    for(NODE_SV *k=dssv;k->next!=NULL;k=k->next)
	{
        if(strcmp(k->data.ma_lop_sv,k->next->data.ma_lop_sv)!=0)
			dem++;
    }

    DS_SV lop[dem];
	unsigned int sl[dem];
	short VT=0;
	
	for(NODE_SV *k=dssv;k->next!=NULL;k=k->next)
    {
        if(strcmp(k->data.ma_lop_sv,k->next->data.ma_lop_sv)==0)
            demSV++;
		else
		{
			sl[VT++]=demSV;
			demSV=1;
		}
		if(k->next->next==NULL)
		{
			sl[VT++]=demSV;
			demSV=1;
		}
    }

	VT = 0;
    lop[VT]=dssv;

	for (NODE_SV *k = dssv->next;k != NULL; k = k->next){
		if (!KiemTraTrungChuoi(k->data.ma_lop_sv,lop[VT]->data.ma_lop_sv))
			lop[++VT] = k;
	}
	
	char kytu;
	short chon = 0;
	short y;
	short i,j;

	loop:
	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"DANH SACH LOP",15,2);
	VeDauBang(chonLop,chonLopSize,chonLopNum,XMINTABLE,YDAUBANG);
	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5, 440, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5, 470, "LEN XUONG DE");
	outtextxy(xMenuChinh+5, 500, "DI CHUYEN");

	y = YTABLE;
	for (j = (chon/10)*10; j < ((chon/10)*10)+10 && j < dem; j++){
		VeDong(chonLopSize,chonLopNum,XMINTABLE,y,0);
		InLopSVTheoDong(lop[j]->data.ma_lop_sv,sl[j],j+1,XMINTABLE,y);
		y+=DONG;
	}
	VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
	InLopSVTheoDong(lop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));

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
								InLopSVTheoDong(lop[j]->data.ma_lop_sv,sl[j],j+1,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLopSVTheoDong(lop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLopSVTheoDong(lop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon--;
						VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLopSVTheoDong(lop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
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
								InLopSVTheoDong(lop[j]->data.ma_lop_sv,sl[j],j+1,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLopSVTheoDong(lop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						y = YTABLE;
						VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLopSVTheoDong(lop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon++;
						VeDong(chonLopSize,chonLopNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLopSVTheoDong(lop[chon]->data.ma_lop_sv,sl[chon],chon+1,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case ESC:
					XoaBang();
					return;
				case ENTER:{
					short stackNum = 0;
					short stt = 1;
					DS_SV dsdk_tam[sl[chon]/10]; // MANG TAM DE LUU CAC NODE DAU CUA 1 TRANG TRONG DANH SACH
					DS_SV nodeChay = lop[chon];
					DS_SV nodeDau = nodeChay;

					// Sap_Xep_DSSV_Theo_LOP(nodeChay, lop[chon]->data.ma_lop_sv);

					XoaBang();
					textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG/2,"BANG THONG KE DIEM TRUNG BINH KHOA HOC",15,2);
					textcenter(XMINTABLE,YDAUBANG/2,XMAXTABLE,100,"LOP: " + convertToString(nodeChay->data.ma_lop_sv),2,15);
					VeDauBang(dtb,dtbSize,dtb_sl,XMINTABLE,YDAUBANG);

					setcolor(0);
					setbkcolor(15);
					outtextxy(xMenuChinh+5, 440, "DUNG MUI TEN");
					outtextxy(xMenuChinh+5, 470, "LEN XUONG DE");
					outtextxy(xMenuChinh+5, 500, "SANG TRANG");

					y = YTABLE;
					for (j = 0; j < 10 && nodeChay != NULL && KiemTraTrungChuoi(nodeDau->data.ma_lop_sv,nodeChay->data.ma_lop_sv); j++){ // IN CAC PHAN TU THEO 1 TRANG
						VeDong(dtbSize,dtb_sl,XMINTABLE,y,0);
						InDiemTrungBinhTheoDong(nodeChay,TinhDiemTrungBinhSv(ds,dsmh,nodeChay->data.ma_sv),stt+j,XMINTABLE,y);
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
										nodeChay = dsdk_tam[--stackNum];
										nodeDau = nodeChay;
										stt -= 10;
										XoaBangDuLieu();
										y = YTABLE;
										for (j = 0; j < 10 && nodeChay != NULL && KiemTraTrungChuoi(nodeDau->data.ma_lop_sv,nodeChay->data.ma_lop_sv); j++){
											VeDong(dtbSize,dtb_sl,XMINTABLE,y,0);
											InDiemTrungBinhTheoDong(nodeChay,TinhDiemTrungBinhSv(ds,dsmh,nodeChay->data.ma_sv),stt+j,XMINTABLE,y);
											nodeChay = nodeChay->next;
											y+=DONG;
										}
									}
									break;
								case KEY_DOWN:
									if (nodeChay != NULL && KiemTraTrungChuoi(nodeDau->data.ma_lop_sv,nodeChay->data.ma_lop_sv)){
										dsdk_tam[stackNum++] = nodeDau;
										nodeDau = nodeChay;
										stt += 10;
										XoaBangDuLieu();
										y = YTABLE;
										for (j = 0; j < 10 && nodeChay != NULL && KiemTraTrungChuoi(nodeDau->data.ma_lop_sv,nodeChay->data.ma_lop_sv); j++){
											VeDong(dtbSize,dtb_sl,XMINTABLE,y,0);
											InDiemTrungBinhTheoDong(nodeChay,TinhDiemTrungBinhSv(ds,dsmh,nodeChay->data.ma_sv),stt+j,XMINTABLE,y);
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
void InThongTinLTC(LOP_TC *lop){
	XoaBang();
	VeBangThem("THONG TIN LOP TIN CHI",lopTinChiLabel,LtcLabelNum);
	setbkcolor(15);
	setcolor(0);
	char tam[10];
	outtextxy(XBANGNHAP+10,YBANGNHAP+7, itoa(lop->ma_lop_tc, tam, 10));
	outtextxy(XBANGNHAP+10,YBANGNHAP+57,lop->ma_mh);
	outtextxy(XBANGNHAP+10,YBANGNHAP+107,itoa(lop->khoa, tam, 10));
	outtextxy(XBANGNHAP+10,YBANGNHAP+157,itoa(lop->hoc_ky, tam, 10));
	outtextxy(XBANGNHAP+10,YBANGNHAP+207,itoa(lop->nhom, tam, 10));
	outtextxy(XBANGNHAP+10,YBANGNHAP+257,itoa(lop->sv_min, tam, 10));
	outtextxy(XBANGNHAP+10,YBANGNHAP+307,itoa(lop->sv_max, tam, 10));
	if (lop->trang_thai) outtextxy(XBANGNHAP+10,YBANGNHAP+357,"MO");
	else outtextxy(XBANGNHAP+10,YBANGNHAP+357,"HUY");
}
void InDanhSachDangKy(LOP_TC *lop, DS_SV dssv){
	short sl = DemSoLuongSVDK(lop->ds_svdk);
	char kytu;
	char tam[10];
	short i,j;
	short y;
	short stackNum = 0;
	DS_SVDK dsdk_tam[sl/10]; // MANG TAM DE LUU CAC NODE DAU CUA 1 TRANG TRONG DANH SACH
	
	DS_SVDK nodeChay = lop->ds_svdk;
	DS_SVDK nodeDau = nodeChay;

	XoaHDSD();
	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5, 440, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5, 470, "LEN XUONG DE");
	outtextxy(xMenuChinh+5, 500, "SANG TRANG");

	XoaBang();
	VeDauBang(TABLEDK,TABLEDKSIZE,TABLEDKNUM,XMINTABLE,YDAUBANG);
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"DANH SACH DANG KY LOP TIN CHI: " + convertToString(itoa(lop->ma_lop_tc, tam, 10)),15,2);
	
	y = YTABLE;
	for (j = 0; j < 10 && nodeChay != NULL; j++){
		VeDong(TABLEDKSIZE,TABLEDKNUM,XMINTABLE,y,0);
		InDsdkTheoDong(dssv,nodeChay->data.ma_sv,j+1,XMINTABLE,y);
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
						nodeChay = dsdk_tam[--stackNum];
						nodeDau = nodeChay;
						XoaBangDuLieu();
						y = YTABLE;
						for (j = 0; j < 10 && nodeChay != NULL; j++){
							VeDong(TABLEDKSIZE,TABLEDKNUM,XMINTABLE,y,0);
							InDsdkTheoDong(dssv,nodeChay->data.ma_sv,j+1,XMINTABLE,y);
							nodeChay = nodeChay->next;
							y+=DONG;
						}
					}
					break;
				case KEY_DOWN:
					if (nodeChay != NULL){
						dsdk_tam[stackNum++] = nodeDau;
						nodeDau = nodeChay;
						XoaBangDuLieu();
						y = YTABLE;
						for (j = 0; j < 10 && nodeChay != NULL; j++){
							VeDong(TABLEDKSIZE,TABLEDKNUM,XMINTABLE,y,0);
							InDsdkTheoDong(dssv,nodeChay->data.ma_sv,j+1,XMINTABLE,y);
							nodeChay = nodeChay->next;
							y+=DONG;
						}
					}
					break;
				case ESC:
					XoaHDSD();
					XoaBang();
					return;
			}
		}
	}
}

bool DocFileLopTinChi(DS_LOP_TC &ds){
	fstream filein;
	filein.open("LopTinChi.txt", ios::in);
	if (filein.fail()){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"GAP LOI KHI MO FILE DE DOC.", "THONG BAO", MB_OK);
		return 1;
	}
	
	string tmpData;
	short slsv, sllop;
	DS_SVDK new_node, cur_node;
	filein >> sllop; getline(filein, tmpData, '\n');
	if (sllop){
		while (ds.n_loptc < sllop){
			ds.ds_ltc[ds.n_loptc] = new LOP_TC;
			filein >> ds.ds_ltc[ds.n_loptc]->ma_lop_tc; getline(filein, tmpData, '\n');
			getline(filein, tmpData, '\n'); // Doc ma mon hoc
			strcpy(ds.ds_ltc[ds.n_loptc]->ma_mh, tmpData.c_str());
			filein >> ds.ds_ltc[ds.n_loptc]->khoa; getline(filein, tmpData, '\n');
			filein >> ds.ds_ltc[ds.n_loptc]->hoc_ky; getline(filein, tmpData, '\n');
			filein >> ds.ds_ltc[ds.n_loptc]->nhom; getline(filein, tmpData, '\n');
			filein >> ds.ds_ltc[ds.n_loptc]->sv_min; getline(filein, tmpData, '\n');
			filein >> ds.ds_ltc[ds.n_loptc]->sv_max; getline(filein, tmpData, '\n');
			filein >> ds.ds_ltc[ds.n_loptc]->trang_thai; getline(filein, tmpData, '\n');
			
			filein >> slsv; getline(filein, tmpData, '\n');
			if (slsv){
				for (short i = 0; i < slsv; i++){
					new_node = new NODE_DK;
					getline(filein, tmpData, ' ');
					strcpy(new_node->data.ma_sv, tmpData.c_str());
					filein >> new_node->data.diem; getline(filein, tmpData, ' ');
					ThemVaoDSDK(ds.ds_ltc[ds.n_loptc],new_node);
				}
			}
			ds.n_loptc++;
		}
		filein.close();
		return 0;
	}
	else{
		filein.close();
		return 1;
	}
}
bool GhiFileLopTinChi(DS_LOP_TC ds){
	fstream fileout;
	fileout.open("LopTinChi.txt", ios::out);
	if (fileout.fail()){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"GAP LOI KHI MO FILE DE GHI.", "THONG BAO", MB_OK);
		return 1;
	}
	fileout.clear();
	fileout << ds.n_loptc;
	if (!ds.n_loptc){
		fileout.close();
		return 1;
	}
	fileout << '\n';
	for (short i = 0; i < ds.n_loptc; i++){
		fileout << ds.ds_ltc[i]->ma_lop_tc; fileout << '\n';
		fileout << ds.ds_ltc[i]->ma_mh; fileout << '\n';
		fileout << ds.ds_ltc[i]->khoa; fileout << '\n';
		fileout << ds.ds_ltc[i]->hoc_ky; fileout << '\n';
		fileout << ds.ds_ltc[i]->nhom; fileout << '\n';
		fileout << ds.ds_ltc[i]->sv_min; fileout << '\n';
		fileout << ds.ds_ltc[i]->sv_max; fileout << '\n';
		fileout << ds.ds_ltc[i]->trang_thai; fileout << '\n';
		if (ds.ds_ltc[i]->ds_svdk == NULL){
			fileout << 0; fileout << '\n';
		} 
		else{
			fileout << DemSoLuongSVDK(ds.ds_ltc[i]->ds_svdk); fileout << '\n';
			DS_SVDK tmp = ds.ds_ltc[i]->ds_svdk;
			while (tmp != NULL){
				fileout << tmp->data.ma_sv; fileout << ' ';
				fileout << tmp->data.diem; fileout << ' ';
				tmp = tmp->next;
			}
			fileout << '\n';
		}
	}
	fileout.close();
	return 0;
}
void KhoiTaoLopTinChi(LOP_TC *lop){
	lop->ma_lop_tc = 0;
	lop->ma_mh[0] = '\0';
	lop->khoa = 0;
	lop->hoc_ky = 0;
	lop->nhom = 0;
	lop->sv_min = 0;
	lop->sv_max = 0;
	lop->trang_thai = false;
	lop->ds_svdk = NULL;
}
void KhoiTaoNodeDangKy(DS_SVDK sv){
	sv->data.diem = -1;
	sv->data.ma_sv[0] = '\0';
	sv->next = NULL;
}
void ThemLopTinChi(DS_LOP_TC &ds, TREE dsmh){
	if (ds.n_loptc == MAX_LOP){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"DANH SACH LOP TIN CHI DA DAY.", "THONG BAO", MB_OK);
		return;
	}
	else if (dsmh == NULL){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"DANH SACH MON HOC RONG.", "THONG BAO", MB_OK);
		return;
	}
	
	
	char tam[10];
	char* mamon;
	short a;

	ds.ds_ltc[ds.n_loptc] = new LOP_TC;
	KhoiTaoLopTinChi(ds.ds_ltc[ds.n_loptc]);

	if (ds.n_loptc == 0) ds.ds_ltc[ds.n_loptc]->ma_lop_tc = 1;
	else{
		unsigned int max = ds.ds_ltc[0]->ma_lop_tc;
		for (short i = 1; i < ds.n_loptc; i++)
			if (ds.ds_ltc[i]->ma_lop_tc > max) max = ds.ds_ltc[i]->ma_lop_tc;
		ds.ds_ltc[ds.n_loptc]->ma_lop_tc = max + 1; // Ma lop tin chi
	}
	
	mamon = ChonMonHoc(dsmh);
	if (mamon == NULL){
		delete ds.ds_ltc[ds.n_loptc];
		return;
	}
	else strcpy(ds.ds_ltc[ds.n_loptc]->ma_mh,mamon);

	VeBangThem("THEM LOP TIN CHI", lopTinChiLabel, LtcLabelNum-1);
	setbkcolor(15);
	setcolor(0);
	itoa(ds.ds_ltc[ds.n_loptc]->ma_lop_tc,tam,10); outtextxy(XBANGNHAP+10,YBANGNHAP+7,tam);
	outtextxy(XBANGNHAP+10,YBANGNHAP+57,mamon);

	NhapNienKhoa(ds.ds_ltc[ds.n_loptc]->khoa,XBANGNHAP,YBANGNHAP+100); // Nien khoa
	if (ds.ds_ltc[ds.n_loptc]->khoa == 0){
		delete ds.ds_ltc[ds.n_loptc];
		return;
	}
	

	NhapHocKy(ds.ds_ltc[ds.n_loptc]->hoc_ky,XBANGNHAP,YBANGNHAP+150); // Hoc ky
	if (ds.ds_ltc[ds.n_loptc]->hoc_ky == 0){
		delete ds.ds_ltc[ds.n_loptc];
		return;
	}

	NhapNhom(ds.ds_ltc[ds.n_loptc]->nhom,XBANGNHAP,YBANGNHAP+200); // Nhom
	if (ds.ds_ltc[ds.n_loptc]->nhom == 0){
		delete ds.ds_ltc[ds.n_loptc];
		return;
	}

	while (KiemTraTrungLTC(ds, ds.ds_ltc[ds.n_loptc]->ma_mh, ds.ds_ltc[ds.n_loptc]->khoa, ds.ds_ltc[ds.n_loptc]->hoc_ky, ds.ds_ltc[ds.n_loptc]->nhom)){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"NHOM NAY DA TON TAI.", "THONG BAO", MB_OK);
		xoa_input(XBANGNHAP,YBANGNHAP+200);
		NhapNhom(ds.ds_ltc[ds.n_loptc]->nhom,XBANGNHAP,YBANGNHAP+200);
		if (ds.ds_ltc[ds.n_loptc]->nhom == 0){
			delete ds.ds_ltc[ds.n_loptc];
			return;
		}
	}

	NhapSoLuongSV(ds.ds_ltc[ds.n_loptc]->sv_min,XBANGNHAP,YBANGNHAP+250); // SV min
	if (ds.ds_ltc[ds.n_loptc]->sv_min == 0){
		delete ds.ds_ltc[ds.n_loptc];
		return;
	}
	NhapSoLuongSV(ds.ds_ltc[ds.n_loptc]->sv_max,XBANGNHAP,YBANGNHAP+300); // SV max
	if (ds.ds_ltc[ds.n_loptc]->sv_max == 0){
		delete ds.ds_ltc[ds.n_loptc];
		return;
	}

	while (ds.ds_ltc[ds.n_loptc]->sv_min > ds.ds_ltc[ds.n_loptc]->sv_max){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"SV MAX KHONG THE NHO HON SV MIN.\nVUI LONG NHAP LAI.", "THONG BAO", MB_OK);
		xoa_input(XBANGNHAP,YBANGNHAP+300);
		NhapSoLuongSV(ds.ds_ltc[ds.n_loptc]->sv_max,XBANGNHAP,YBANGNHAP+300);
		if (ds.ds_ltc[ds.n_loptc]->sv_max == 0){
			delete ds.ds_ltc[ds.n_loptc];
			return;
		}
	}

	ds.n_loptc++;
	MessageBox(NULL,"THEM LOP TIN CHI THANH CONG.", "THONG BAO", MB_OK);
	return ThemLopTinChi(ds,dsmh);
}
bool KiemTraTrungChuoi(char *chuoi1, char *chuoi2){
	if (strlen(chuoi1) == strlen(chuoi2)){
		for(short i = 0; i < strlen(chuoi1); i++)
			if (chuoi1[i] != chuoi2[i]) return 0; // Khong trung
		return 1; // Trung
	}
	else return 0; // Khong trung
}
bool KiemTraTrungLTC(DS_LOP_TC ds, char *ma_mh, unsigned short nienkhoa, unsigned short hocky, unsigned short nhom){
	short i;
	for (i = 0; i < ds.n_loptc; i++){
		if (KiemTraTrungChuoi(ds.ds_ltc[i]->ma_mh,ma_mh) && ds.ds_ltc[i]->khoa == nienkhoa && ds.ds_ltc[i]->hoc_ky == hocky && ds.ds_ltc[i]->nhom == nhom) return 1;
	}	
	return 0;
}
short TimKiemLopTinChi(DS_LOP_TC ds, unsigned int maLop){
	for (short i = 0; i < ds.n_loptc; i++)
		if (ds.ds_ltc[i]->ma_lop_tc == maLop) return i;
	return -1;
}
short TimKiemLopTinChi(LOP_TC* mang[], short sl, unsigned maLop){
	for (short i = 0; i < sl; i++)
		if (mang[i]->ma_lop_tc == maLop) return i;
	return -1;
}
int DemSoLuongSVDK(DS_SVDK ds){
	int count = 0;
	while (ds != NULL){
	 	count++;
	 	ds = ds->next;
	}
	return count;
}
void HuyLopTinChi(LOP_TC *lop){
	short count = DemSoLuongSVDK(lop->ds_svdk);
	if (count < lop->sv_min) lop->trang_thai = false;
	else lop->trang_thai = true;
}
void AutoHuyLopTinChi(DS_LOP_TC &ds){
	if (ds.n_loptc == 0){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"KHONG CO LOP TIN CHI NAO TRONG DANH SACH.", "THONG BAO", MB_OK);
		return;
	}

	string label[2] = {"NIEN KHOA", "HOC KY"};
	VeBangThem("TU DONG HUY LOP TIN CHI", label, 2);

	short x = XBANGNHAP, y = YBANGNHAP;
	unsigned short nk = 0,hk = 0;

	NhapNienKhoa(nk,x,y);
	if (nk == 0) return;

	NhapHocKy(hk,x,y+50);
	if (hk == 0) return;

	XoaBang();

	short ltc_count = 0;
	int i,j;
	char kytu;

	for (i = 0; i < ds.n_loptc; i++)
		if (ds.ds_ltc[i]->khoa == nk && ds.ds_ltc[i]->hoc_ky == hk) ltc_count++; // DEM SO LUONG LOP TRONG HOC KY
	
	if (ltc_count == 0){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"KHONG CO LOP TIN CHI NAO MO TRONG KY NAY.", "THONG BAO", MB_OK);
		return;
	}

	LOP_TC *lop_tam[ltc_count];
	
	j = 0;
	for (i = 0; i < ds.n_loptc; i++){
		if (ds.ds_ltc[i]->khoa == nk && ds.ds_ltc[i]->hoc_ky == hk)
			lop_tam[j++] = ds.ds_ltc[i];
	}

	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"TU DONG HUY LOP TIN CHI",15,2);
	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5, 440, "F5: TU DONG HUY");
	outtextxy(xMenuChinh+5, 470, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5, 500, "LEN XUONG DE");
	outtextxy(xMenuChinh+5, 530, "SANG TRANG");

	in:
	i = 0;
	XoaBangDuLieu();
	VeDauBang(TABLELTC2,TABLELTCSIZE2,TABLELTCNUM2,XMINTABLE,YDAUBANG);

	y = YTABLE;
	for (j = i; j < i + 10 && j < ltc_count; j++){
		VeDong(TABLELTCSIZE2,TABLELTCNUM2,XMINTABLE,y,0);
		InLtcTheoDong(lop_tam[j],j+1,XMINTABLE,y);
		y+=DONG;
	}

	while (1){
		delay(10);
		if (kbhit()){
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu){
				case KEY_UP:
					if (i >= 10){
						i -= 10;
						XoaBangDuLieu();
						y = YTABLE;
						for (j = i; j < ltc_count && j < i + 10; j++){
							VeDong(TABLELTCSIZE2,TABLELTCNUM2,XMINTABLE,y,0);
							InLtcTheoDong(lop_tam[j],j+1,XMINTABLE,y);
							y+=DONG;
						}
					}
					break;
				case KEY_DOWN:
					if (ltc_count - i > 10){
						i += 10;
						XoaBangDuLieu();
						y = YTABLE;
						for (j = i; j < ltc_count && j < i + 10; j++){
							VeDong(TABLELTCSIZE2,TABLELTCNUM2,XMINTABLE,y,0);
							InLtcTheoDong(lop_tam[j],j+1,XMINTABLE,y);
							y+=DONG;
						}
					}
					break;
				case KEY_F5:{
					short a = MessageBox(NULL,"NHUNG LOP CO SO LUONG SV DANG KY NHO HON SV MIN SE BI HUY.","THONG BAO", MB_YESNO);
					if (a == 6){
						for (j = 0; j < ltc_count; j++) HuyLopTinChi(lop_tam[j]);
						goto in;
					} 
					break;
				}
				case ESC:
					XoaBang();
					return;
			}
		}
	}
}
bool KiemTraDaDangKy(DS_SVDK ds, char *mssv){
	DS_SVDK nodeChay = ds;
	while (nodeChay != NULL){
		if (KiemTraTrungChuoi(nodeChay->data.ma_sv,mssv)) return 1;
		nodeChay = nodeChay->next;
	}
	return 0;
}
bool KiemTraDangKyTrungMon(LOP_TC *mang[], short soLuong, bool* ttdk, bool* thaydoi, short chon){
	// DANH SACH DUOC SAP XEP THEO THU TU TEN MON TANG DAN
	short i=chon-1,j=chon+1;
	while (i != -1 && KiemTraTrungChuoi(mang[i]->ma_mh,mang[chon]->ma_mh)){
		if ((ttdk[i] && !thaydoi[i]) || (!ttdk[i] && thaydoi[i])) return 1;
		else i--;
	}
	while (j != soLuong && KiemTraTrungChuoi(mang[j]->ma_mh,mang[chon]->ma_mh)){
		if ((ttdk[j] && !thaydoi[j]) || (!ttdk[j] && thaydoi[j])) return 1;
		else j++;
	}
	return 0;
}
bool KiemTraDaCoDiem(LOP_TC *lop){
	if (lop->ds_svdk == NULL) return false;
	DS_SVDK nodeChay = lop->ds_svdk;
	while (nodeChay != NULL){
		if (nodeChay->data.diem == -1) return false;
		nodeChay = nodeChay->next;
	}
	return true;
}
void ThemVaoDSDK(LOP_TC *lop, DS_SVDK ref){ // THEM DAM BAO THU TU TANG DEN THEO MA SINH VIEN
	if (DemSoLuongSVDK(lop->ds_svdk) == lop->sv_max){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "LOP DA DAY.", "THONG BAO", MB_OK);
		return;
	}

	DS_SVDK nodeMoi = new NODE_DK;
	nodeMoi->data = ref->data; nodeMoi->next = NULL;

	DS_SVDK nodeChay = lop->ds_svdk;
	if (nodeChay == NULL){
		nodeMoi->next = NULL;
		lop->ds_svdk = nodeMoi;
		return;
	}
	DS_SVDK prev = NULL;
	while (nodeChay != NULL){
		if (strcmp(nodeMoi->data.ma_sv,nodeChay->data.ma_sv) > 0){
			prev = nodeChay;
			nodeChay = nodeChay->next;
		}
		else break;
	}
	if (prev == NULL){
		nodeMoi->next = nodeChay;
		lop->ds_svdk = nodeMoi;
		return;
	}
	nodeMoi->next = nodeChay;
	prev->next = nodeMoi;
}
void XoaSvTrongDSDK(DS_SVDK &ds, char* mssv){
	DS_SVDK cur, prev;
	cur = ds;
	prev = NULL;
	while (cur != NULL){
		if (strcmp(cur->data.ma_sv,mssv) != 0){
			prev = cur;
			cur = cur->next;
		}
		else break;
	}
	if (prev == NULL){
		prev = cur;
		ds = cur->next;
		delete prev;
	}
	else{
		prev->next = cur->next;
		delete cur;
	}
}
void DangKyLopTinChi(DS_LOP_TC &dsltc, DS_SV dssv, TREE dsmh){
	XoaBang();
	DS_SV nodeChay = dssv;
	SINH_VIEN *luuTru;

	if (nodeChay == NULL){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "DANH SACH SINH VIEN TRONG.", "THONG BAO", MB_OK);
		return;
	}

	string label[3] = {"MSSV", "NIEN KHOA", "HOC KY"};
	VeBangThem("DANG KY MON HOC", label, 3);

	short x = XBANGNHAP, y = YBANGNHAP;
	DS_SVDK tam = new NODE_DK;
	KhoiTaoNodeDangKy(tam);

	NhapMa(tam->data.ma_sv,17,1,x,y);
	if (tam->data.ma_sv[0] == '\0') return;

	while (nodeChay != NULL){
		if (KiemTraTrungChuoi(nodeChay->data.ma_sv,tam->data.ma_sv) == 0) nodeChay = nodeChay->next;
		else{
			luuTru = &(nodeChay->data);
			break;
		}
	}

	if (nodeChay == NULL){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "SINH VIEN KHONG TON TAI.", "THONG BAO", MB_OK);
		return DangKyLopTinChi(dsltc,dssv,dsmh);
	}
	else{
		unsigned short nk = 0,hk = 0;
		short ltc_count = 0;

		NhapNienKhoa(nk,x,y+50);
		if (nk == 0) return;

		NhapHocKy(hk,x,y+100);
		if (hk == 0) return;

		for (short i = 0; i < dsltc.n_loptc; i++)
			if (dsltc.ds_ltc[i]->khoa == nk && dsltc.ds_ltc[i]->hoc_ky == hk) ltc_count++;

		if (ltc_count){
			setfillstyle(SOLID_FILL,3);
			bar(20,440,50,456); outtextxy(55,440,": DA DANG KY");
			setcolor(0);
			setbkcolor(15);
			outtextxy(xMenuChinh+5, 470, "DUNG MUI TEN");
			outtextxy(xMenuChinh+5, 500, "LEN XUONG DE");
			outtextxy(xMenuChinh+5, 530, "DI CHUYEN");

			LOP_TC *lop_tam[ltc_count];
			bool ttdk[ltc_count]; // TRANG THAI DANG KY LOP BAN DAU CUA SINH VIEN
			bool thaydoi[ltc_count]; // THAY DOI SO VOI DANG KY BAN DAU
			short slsv[ltc_count];

			short j = 0;

			for (short i = 0; i < dsltc.n_loptc; i++)
				if (dsltc.ds_ltc[i]->khoa == nk && dsltc.ds_ltc[i]->hoc_ky == hk){
					if (KiemTraDaDangKy(dsltc.ds_ltc[i]->ds_svdk,tam->data.ma_sv)) ttdk[j] = 1;
					else ttdk[j] = 0;
					thaydoi[j] = 0;
					slsv[j] = DemSoLuongSVDK(dsltc.ds_ltc[i]->ds_svdk);
					lop_tam[j++] = dsltc.ds_ltc[i];
				}

			char so[5];
			char kytu;
			short chon = 0;

			QuickSortTheoTenMon(lop_tam,ttdk,thaydoi,slsv,dsmh,0,ltc_count-1);

			XoaBang();
			textcenter(XMINTABLE,10,XMAXTABLE,40,"HO TEN: " + convertToString(luuTru->ho) + " " + convertToString(luuTru->ten),1,15);
			textcenter(XMINTABLE,40,XMAXTABLE,70,"MSSV: " + convertToString(luuTru->ma_sv),1,15);
			textcenter(XMINTABLE,70,XMAXTABLE,100,"LOP: " + convertToString(luuTru->ma_lop_sv),1,15);
			textcenter(XMINTABLE,100,XMAXTABLE,130,"NIEN KHOA: " + convertToString(itoa(nk,so,10)) + " - " + "HOC KY: " + convertToString(itoa(hk,so,10)),1,15);

			VeDauBang(dangKyMonLabel,dkmSize,DkmLabelNum,XMINTABLE,YDAUBANG);
			
			y = YTABLE;
			for (j = 0; j < 10 && j < ltc_count; j++){
				if ((ttdk[j] && !thaydoi[j]) || (!ttdk[j] && thaydoi[j]))
					VeDong(dkmSize,DkmLabelNum,XMINTABLE,y,1);
				else
					VeDong(dkmSize,DkmLabelNum,XMINTABLE,y,0);
				InDangKyMonTheoDong(lop_tam[j],dsmh,slsv[j],XMINTABLE,y);
				y+=DONG;
			}
			VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
			InDangKyMonTheoDong(lop_tam[chon],dsmh,slsv[chon],XMINTABLE,YTABLE+(DONG*(chon%10)));
			
			while (1){
				delay(10);
				if(kbhit()){
					kytu = getch();
					if (kytu == -32) kytu = getch();
					switch(kytu){
						case KEY_UP:
							if (chon > 0){
								if (chon % 10 == 0){
									XoaBangDuLieu();
									chon--;
									y = YTABLE;
									for (j = chon-9; j <= chon; j++){
										if ((ttdk[j] && !thaydoi[j]) || (!ttdk[j] && thaydoi[j]))
											VeDong(dkmSize,DkmLabelNum,XMINTABLE,y,1);
										else
											VeDong(dkmSize,DkmLabelNum,XMINTABLE,y,0);
										InDangKyMonTheoDong(lop_tam[j],dsmh,slsv[j],XMINTABLE,y);
										y+=DONG;
									}
									VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+(DONG*(chon%10)),2);
									InDangKyMonTheoDong(lop_tam[chon],dsmh,slsv[chon],XMINTABLE,YTABLE+(DONG*(chon%10)));
									break;
								}
								// y = YTABLE;
									if ((ttdk[chon] && !thaydoi[chon]) || (!ttdk[chon] && thaydoi[chon])) 
										VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),1);
									else
										VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
								InDangKyMonTheoDong(lop_tam[chon],dsmh,slsv[chon],XMINTABLE,YTABLE+((chon%10)*DONG));
								chon--;
								VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
								InDangKyMonTheoDong(lop_tam[chon],dsmh,slsv[chon],XMINTABLE,YTABLE+(DONG*(chon%10)));
							}
							break;
						case KEY_DOWN:
							if (chon + 1 < ltc_count){
								if ((chon + 1) % 10 == 0){
									XoaBangDuLieu();
									chon++;
									short conlai = ltc_count - chon >= 10 ? 10 : ltc_count - chon;
									y = YTABLE;
									for (j = chon; j < chon + conlai; j++){
										if ((ttdk[j] && !thaydoi[j]) || (!ttdk[j] && thaydoi[j]))
											VeDong(dkmSize,DkmLabelNum,XMINTABLE,y,1);
										else
											VeDong(dkmSize,DkmLabelNum,XMINTABLE,y,0);
										InDangKyMonTheoDong(lop_tam[j],dsmh,slsv[j],XMINTABLE,y);
										y+=DONG;
									}
									VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+(DONG*(chon%10)),2);
									InDangKyMonTheoDong(lop_tam[chon],dsmh,slsv[chon],XMINTABLE,YTABLE+(DONG*(chon%10)));
									break;
								}
								y = YTABLE;
								if ((ttdk[chon] && !thaydoi[chon]) || (!ttdk[chon] && thaydoi[chon]))
									VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),1);
								else
									VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
								InDangKyMonTheoDong(lop_tam[chon],dsmh,slsv[chon],XMINTABLE,YTABLE+((chon%10)*DONG));
								chon++;
								VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
								InDangKyMonTheoDong(lop_tam[chon],dsmh,slsv[chon],XMINTABLE,YTABLE+(DONG*(chon%10)));
							}
							break;
						case ENTER:
							if (lop_tam[chon]->trang_thai){
								MessageBeep(0xFFFFFFFF);
								MessageBox(NULL,"LOP NAY DA MO. KHONG THE DANG KY HOAC HUY DANG KY.", "THONG BAO", MB_OK);
							}
							else{ // LOP CHUA MO
								if (KiemTraDangKyTrungMon(lop_tam,ltc_count,ttdk,thaydoi,chon)){
									MessageBeep(0xFFFFFFFF);
									MessageBox(NULL,"SINH VIEN DA DANG KY MON NAY.", "THONG BAO", MB_OK);
								}
								else{
									if (ttdk[chon]){ // DA DANG KY
										if (thaydoi[chon]){
											slsv[chon]++;
											thaydoi[chon] = 0;
										}
										else{
											slsv[chon]--;
											thaydoi[chon] = 1;
										}
										VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
										InDangKyMonTheoDong(lop_tam[chon],dsmh,slsv[chon],XMINTABLE,YTABLE+(DONG*(chon%10)));
									}
									else{ // CHUA DANG KY
										if (thaydoi[chon]){
											slsv[chon]--;
											thaydoi[chon] = 0;
										}
										else{
											if (slsv[chon] < lop_tam[chon]->sv_max){
												slsv[chon]++;
												thaydoi[chon] = 1;
											}
											else{
												MessageBeep(0xFFFFFFFF);
												MessageBox(NULL,"LOP DA DAY.", "THONG BAO", MB_OK);
												break;
											}
										}
										VeDong(dkmSize,DkmLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
										InDangKyMonTheoDong(lop_tam[chon],dsmh,slsv[chon],XMINTABLE,YTABLE+(DONG*(chon%10)));
									}
								}
							}
							break;
						case KEY_F4:
						case ESC:
							short a = MessageBox(NULL,"BAN CO MUON LUU?", "THONG BAO", MB_YESNO);
							if (a == 6){
								for (j = 0; j < ltc_count; j++){
									if (thaydoi[j]){
										if (ttdk[j]) XoaSvTrongDSDK(lop_tam[j]->ds_svdk, tam->data.ma_sv);
										else ThemVaoDSDK(lop_tam[j],tam);
									}
								}
								delete tam;
								MessageBox(NULL,"DANG KY MON THANH CONG.", "THONG BAO", MB_OK);
								XoaBang();
							}
							return;
					}
				}
			}
		}
		else{
			MessageBeep(0xFFFFFFFF);
			MessageBox(NULL,"KHONG CO LOP TIN CHI NAO MO TRONG KY NAY.", "THONG BAO", MB_OK);
			return DangKyLopTinChi(dsltc,dssv,dsmh);
		} 
	}
}
void SuaLopTinChi(DS_LOP_TC &ds, TREE dsmh, short vitri){
	XoaBang();
	XoaHDSD();
	char* mamon = ds.ds_ltc[vitri]->ma_mh;
	unsigned short nk=ds.ds_ltc[vitri]->khoa;
	unsigned short hk=ds.ds_ltc[vitri]->hoc_ky;
	unsigned short nhom=ds.ds_ltc[vitri]->nhom;
	unsigned short svmin=ds.ds_ltc[vitri]->sv_min;
	unsigned short svmax=ds.ds_ltc[vitri]->sv_max;
	short a;

	if (ds.ds_ltc[vitri]->ds_svdk == NULL){
		// mamon = ChonMonHoc(dsmh);
		// if (mamon == NULL) return;
		// else{
		// 	XoaBang();
		// 	VeBangThem("SUA LOP TIN CHI",lopTinChiLabel,LtcLabelNum-1);
		// 	setbkcolor(15);
		// 	setcolor(0);
		// 	char tam[10];
		// 	InThongTinLTC(ds.ds_ltc[vitri]);
		// 	xoa_input(XBANGNHAP,YBANGNHAP+50);
		// 	outtextxy(XBANGNHAP+10,YBANGNHAP+57,mamon); // Ma mon hoc
		// }

		InThongTinLTC(ds.ds_ltc[vitri]);

		NhapNienKhoa(nk,XBANGNHAP,YBANGNHAP+100); // Nhap lai nien khoa
		if (nk == 0) return;
		NhapHocKy(hk,XBANGNHAP,YBANGNHAP+150); // Nhap lai hoc ky
		if (hk == 0) return;

		NhapNhom(nhom,XBANGNHAP,YBANGNHAP+200); // Nhap lai nhom
		if (nhom == 0) return;

		while (KiemTraTrungLTC(ds, ds.ds_ltc[vitri]->ma_mh, nk, hk, nhom)){
			MessageBeep(0xFFFFFFFF);
			MessageBox(NULL,"NHOM NAY DA TON TAI.", "THONG BAO", MB_OK);
			xoa_input(XBANGNHAP,YBANGNHAP+200);
			NhapNhom(nhom,XBANGNHAP,YBANGNHAP+200);
			if (nhom == 0) return;
		}
	}
	else InThongTinLTC(ds.ds_ltc[vitri]);

	NhapSoLuongSV(svmin,XBANGNHAP,YBANGNHAP+250); // SV min
	if (svmin == 0) return;
	NhapSoLuongSV(svmax,XBANGNHAP,YBANGNHAP+300); // SV max
	if (svmax == 0) return;
	while (svmin > svmax || svmax < DemSoLuongSVDK(ds.ds_ltc[vitri]->ds_svdk)){
		if (svmin > svmax){
			MessageBeep(0xFFFFFFFF);
			MessageBox(NULL,"SV MAX KHONG THE NHO HON SV MIN.\nVUI LONG NHAP LAI.", "THONG BAO", MB_OK);
		}
		else if (svmax < DemSoLuongSVDK(ds.ds_ltc[vitri]->ds_svdk)){
			MessageBeep(0xFFFFFFFF);
			MessageBox(NULL,"SV MAX PHAI LON HON SO LUONG SINH VIEN DA DANG KY.\nVUI LONG NHAP LAI.", "THONG BAO", MB_OK);
		}
		xoa_input(XBANGNHAP,YBANGNHAP+300);
		NhapSoLuongSV(svmax,XBANGNHAP,YBANGNHAP+300);
		if (svmax == 0) return;
	}

	strcpy(ds.ds_ltc[vitri]->ma_mh,mamon);
	ds.ds_ltc[vitri]->khoa = nk;
	ds.ds_ltc[vitri]->hoc_ky = hk;
	ds.ds_ltc[vitri]->nhom = nhom;
	ds.ds_ltc[vitri]->sv_min = svmin;
	ds.ds_ltc[vitri]->sv_max = svmax;
	MessageBox(NULL,"SUA LOP TIN CHI THANH CONG.", "THONG BAO", MB_OK);
}
void GiaiPhongDanhSachDangKy(DS_SVDK &ds){
	if (ds == NULL) return;
	DS_SVDK nodeXoa;
	while (ds != NULL){
		nodeXoa = ds;
		ds = ds->next;
		delete nodeXoa;
	}
}
void XoaLopTinChi(DS_LOP_TC &ds, short vitri){
	GiaiPhongDanhSachDangKy(ds.ds_ltc[vitri]->ds_svdk);
	delete ds.ds_ltc[vitri];

	while (vitri < ds.n_loptc - 1)
	{
		ds.ds_ltc[vitri] = ds.ds_ltc[vitri + 1];
		vitri++;
	}

	ds.n_loptc--;
	MessageBox(NULL,"XOA LOP TIN CHI THANH CONG.", "THONG BAO", MB_OK);
}
bool SoSanhLopTinChi(LOP_TC* index, LOP_TC* pivot){
	if (strcmp(index->ma_mh,pivot->ma_mh) > 0) return 1;
	else if (strcmp(index->ma_mh,pivot->ma_mh) < 0) return 0;
	else{
		if (index->khoa < pivot->khoa) return 1;
		else if (index->khoa > pivot->khoa) return 0;
		else{
			if (index->hoc_ky < pivot->hoc_ky) return 1;
			else if (index->hoc_ky > pivot->hoc_ky) return 0;
		}
	}
}
bool SoSanhTheoTenVaMaMon(TREE dsmh, LOP_TC* index, LOP_TC* pivot){
	if (strcmp(Tim_MonHocTheo_MaMon(dsmh,atoi(index->ma_mh))->ten_mh,Tim_MonHocTheo_MaMon(dsmh,atoi(pivot->ma_mh))->ten_mh) < 0) return 1;
	else if (strcmp(Tim_MonHocTheo_MaMon(dsmh,atoi(index->ma_mh))->ten_mh,Tim_MonHocTheo_MaMon(dsmh,atoi(pivot->ma_mh))->ten_mh) > 0) return 0;
	else{
		if (strcmp(index->ma_mh,pivot->ma_mh) < 0) return 1;
		else if (strcmp(index->ma_mh,pivot->ma_mh) > 0) return 0;
	}
}
int partitionTichHop(DS_LOP_TC &ds, short low, short high){
	LOP_TC* pivot = ds.ds_ltc[high];
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && !SoSanhLopTinChi(ds.ds_ltc[left],pivot)) left++;
        while(right >= left && SoSanhLopTinChi(ds.ds_ltc[right],pivot)) right--;
        if (left >= right) break;
        swap(ds.ds_ltc[left], ds.ds_ltc[right]);
        left++;
        right--;
    }
    swap(ds.ds_ltc[left], ds.ds_ltc[high]);
    return left;
}
void swap(LOP_TC* &a, LOP_TC* &b){
	LOP_TC* c = a;
	a = b;
	b = c;
}
void swapBool(bool &a, bool &b){
	bool c = a;
	a = b;
	b = c;
}
void swapShort(short &a, short &b){
	short c = a;
	a = b;
	b = c;
}
int partitionTheoTenMon(DS_LOP_TC &ds, TREE dsmh, short low, short high){
	LOP_TC* pivot = ds.ds_ltc[high];
    int left = low;
    int right = high - 1;
	unsigned short  pValue = 0;
    while(true){
        while(left <= right && SoSanhTheoTenVaMaMon(dsmh,ds.ds_ltc[left],pivot)) left++;
        while(right >= left && !SoSanhTheoTenVaMaMon(dsmh,ds.ds_ltc[right],pivot)) right--;
        if (left >= right) break;
        swap(ds.ds_ltc[left], ds.ds_ltc[right]);
        left++;
        right--;
    }
    swap(ds.ds_ltc[left], ds.ds_ltc[high]);
    return left;
}
int partitionTheoTenMon(LOP_TC* mang[], bool* ttdk, bool* thaydoi, short* slsv, TREE dsmh, short low, short high){
	LOP_TC* pivot = mang[high];
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && SoSanhTheoTenVaMaMon(dsmh,mang[left],pivot)) left++;
        while(right >= left && !SoSanhTheoTenVaMaMon(dsmh,mang[right],pivot)) right--;
        if (left >= right) break;
        swap(mang[left], mang[right]);
		swapBool(ttdk[left],ttdk[right]);
		swapBool(thaydoi[left],thaydoi[right]);
		swapShort(slsv[left],slsv[right]);
        left++;
        right--;
    }
    swap(mang[left], mang[high]);
	swapBool(ttdk[left],ttdk[high]);
	swapBool(thaydoi[left],thaydoi[high]);
	swapShort(slsv[left],slsv[high]);
    return left;
}
void QuickSortTheoTenMon(LOP_TC* mang[], bool* ttdk, bool* thaydoi, short* slsv, TREE dsmh, short low, short high){
	if (low < high)
    {
        short pi = partitionTheoTenMon(mang, ttdk, thaydoi, slsv, dsmh, low, high);
        QuickSortTheoTenMon(mang, ttdk, thaydoi, slsv, dsmh, low, pi - 1);
        QuickSortTheoTenMon(mang, ttdk, thaydoi, slsv, dsmh, pi + 1, high);
    }
}
void QuickSortTheoTenMon(DS_LOP_TC &ds, TREE dsmh, short low, short high){
	if (low < high)
    {
        short pi = partitionTheoTenMon(ds, dsmh, low, high);
        QuickSortTheoTenMon(ds, dsmh, low, pi - 1);
        QuickSortTheoTenMon(ds, dsmh, pi + 1, high);
    }
}
void QuickSortTichHop(DS_LOP_TC &ds, short low, short high){
	if (low < high)
    {
        short pi = partitionTichHop(ds, low, high);
        QuickSortTichHop(ds, low, pi - 1);
        QuickSortTichHop(ds, pi + 1, high);
    }
}
void GiaiPhongDSLTC(DS_LOP_TC &ds){
	for (short i = 0; i < ds.n_loptc; i++){
		GiaiPhongDanhSachDangKy(ds.ds_ltc[i]->ds_svdk);
		delete ds.ds_ltc[i];
	}
}
void ChucNangNhapDiem(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh){
	if (ds.n_loptc == 0){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "KHONG CO LOP TIN CHI NAO TRONG DANH SACH.", "THONG BAO", MB_OK);
		return;
	}
	short chon = 0;
	short y = 0;
	char kytu;

	short sl = 0;
	for (short i = 0; i < ds.n_loptc; i++) if (ds.ds_ltc[i]->trang_thai) sl++;
	
	if (sl == 0){
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL, "KHONG CO LOP TIN CHI NAO DUOC MO.", "THONG BAO", MB_OK);
		return;
	}

	LOP_TC* loptam[sl]; // mang con tro cung cap tro den cac lop tin chi trong danh sach

	for (short i = 0; i < ds.n_loptc; i++) if (ds.ds_ltc[i]->trang_thai) loptam[y++] = ds.ds_ltc[i]; // bat dau tro

	loop:
	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"NHAP DIEM CHO LOP TIN CHI",15,2);
	VeDauBang(TABLELTC,TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YDAUBANG);
	setcolor(0);
	setbkcolor(15);
	
	outtextxy(xMenuChinh+5, 440, "F1: TIM KIEM");
	outtextxy(xMenuChinh+5, 470, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5, 500, "LEN XUONG DE");
	outtextxy(xMenuChinh+5, 530, "DI CHUYEN");
	
	
	y = YTABLE;
	for (short j = (chon/10)*10; j < ((chon/10)*10)+10 && j < sl; j++){
		VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
		InLtcTheoDong(loptam[j],dsmh,XMINTABLE,y);
		y+=DONG;
	}
	
	VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
	InLtcTheoDong(loptam[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
	
	while (1){
		delay(10);
		if (kbhit()){
			kytu = getch();
			if (kytu == -32) kytu = getch();
			switch(kytu){
				case KEY_UP:
					if (chon > 0){
						if (chon % 10 == 0)
						{
							XoaBangDuLieu();
							chon--;
							y = YTABLE;
							for (short j = chon-9; j <= chon; j++)
							{
								VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
								InLtcTheoDong(loptam[j],dsmh,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLtcTheoDong(loptam[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						// y = YTABLE;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLtcTheoDong(loptam[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon--;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLtcTheoDong(loptam[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case KEY_DOWN:
					if (chon + 1 < sl){
						if ((chon + 1) % 10 == 0)
						{
							XoaBangDuLieu();
							chon++;
							short conlai = sl - chon >= 10 ? 10 : sl - chon;
							y = YTABLE;
							for (short j = chon; j < chon + conlai; j++)
							{
								VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,y,0);
								// InLtcTheoDong(loptam[j],j+1,XMINTABLE,y);
								InLtcTheoDong(loptam[j],dsmh,XMINTABLE,y);
								y+=DONG;
							}
							VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
							InLtcTheoDong(loptam[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
							break;
						}
						// y = YTABLE;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InLtcTheoDong(loptam[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
						chon++;
						VeDong(TABLELTCSIZE,TABLELTCNUM,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InLtcTheoDong(loptam[chon],dsmh,XMINTABLE,YTABLE+(DONG*(chon%10)));
					}
					break;
				case ENTER:{
					short slsv = DemSoLuongSVDK(loptam[chon]->ds_svdk);
					NhapDiemChoLopTinChi(loptam[chon],slsv,dssv,dsmh);
					goto loop;
				}
				case KEY_F1:{
					string label[4] = {"NIEN KHOA", "HOC KY", "NHOM", "MA MON"};

					unsigned short nk,hk,nhom;
					char tam[4]; 
					char* mamon;
					short i;

					nhaplai:
					XoaBang();
					VeBangThem("TIM KIEM LOP TIN CHI",label,4);
					tam[0] = '\0';
					nk = hk = nhom = 0;
					
					xoa_input(XBANGNHAP,YBANGNHAP);
					NhapNienKhoa(nk,XBANGNHAP,YBANGNHAP);
					if (nk == 0) goto loop;

					xoa_input(XBANGNHAP,YBANGNHAP+50);
					NhapHocKy(hk,XBANGNHAP,YBANGNHAP+50);
					if (hk == 0) goto loop;

					xoa_input(XBANGNHAP,YBANGNHAP+100);
					NhapMa(tam,4,0,XBANGNHAP,YBANGNHAP+100); // Nhom
					nhom = atoi(tam);
					while (nhom == 0){
						if (tam[0] == '\0') return;
						MessageBeep(0xFFFFFFFF);
						MessageBox(NULL,"NHOM PHAI KHAC 0.", "THONG BAO", MB_OK);
						xoa_input(XBANGNHAP,YBANGNHAP+100);
						tam[0] = '\0';
						NhapMa(tam,4,0,XBANGNHAP,YBANGNHAP+100);
					}

					mamon = ChonMonHoc(dsmh);
					if (mamon == NULL) return;

					for (i = 0; i < sl; i++){
						if (KiemTraTrungChuoi(loptam[i]->ma_mh,mamon) && loptam[i]->khoa == nk && loptam[i]->hoc_ky == hk && loptam[i]->nhom == nhom){
							short slsv = DemSoLuongSVDK(loptam[i]->ds_svdk);
							NhapDiemChoLopTinChi(loptam[i],slsv,dssv,dsmh);
							goto loop;
						}
					}
					MessageBeep(0xFFFFFFFF);
					MessageBoxA(NULL, "LOP DANG TRONG TRANG THAI HUY HOAC KHONG TON TAI.", "THONG BAO", MB_OK);
					goto nhaplai;
				}
				case ESC: return;
			}
		}
	}
}

float TinhDiemTrungBinhSv(DS_LOP_TC &ds, TREE dsmh, char *masv){
	float tong = 0.0;
	int mau = 0;
	bool flag = 1;
	DS_SVDK nodeChay;
	MON_HOC* mon;

	for (short i = 0; i < ds.n_loptc; i++){
		if (!ds.ds_ltc[i]->trang_thai) continue;
		if (flag){
			nodeChay = ds.ds_ltc[i]->ds_svdk;
			while (nodeChay != NULL){
				if (KiemTraTrungChuoi(nodeChay->data.ma_sv,masv) && nodeChay->data.diem != -1){
					mon = Tim_MonHocTheo_MaMon(dsmh,atoi(ds.ds_ltc[i]->ma_mh));
					tong += nodeChay->data.diem * (mon->stc_lt + mon->stc_th); // NHAN THEM SO TIN CHI
					mau += (mon->stc_lt + mon->stc_th); // CONG THEM SO TIN CHI
					flag = 0;
					break;
				}
				else if (strcmp(nodeChay->data.ma_sv,masv) > 0) break;
				else nodeChay = nodeChay->next;
			}
		}
		if (!KiemTraTrungChuoi(ds.ds_ltc[i]->ma_mh,ds.ds_ltc[i + 1 == ds.n_loptc ? -1 : i + 1]->ma_mh)) flag = 1;
	}
	mau = mau > 0 ? mau : 1;
	return tong/mau;
}
void InDiemTheoDong(DS_SV dssv, DANG_KI *sv, short stt, short x, short y){
	char tam[5];
	outtextxy(x+5,y+12,itoa(stt,tam,10));
	x+= diemSize[0]; outtextxy(x+5,y+12,sv->ma_sv);
	DS_SV nodeTam = Check_maSV_TrongDSSV1(dssv,sv->ma_sv);
	x+= diemSize[1]; outtextxy(x+5,y+12,nodeTam->data.ho);
	x+= diemSize[2]; outtextxy(x+5,y+12,nodeTam->data.ten);
	x+= diemSize[3];
	if (sv->diem == -1) outtextxy(x+5,y+12," ");
	else{
		ftoa(sv->diem,tam);
		outtextxy(x+5,y+12,tam);
	}
}
void NhapDiemChoLopTinChi(LOP_TC* lop, short slsv, DS_SV dssv, TREE dsmh){
	char tam[10];
	XoaBang();
	XoaHDSD();
	textcenter(XMINTABLE,10,XMAXTABLE,70,"MON " + convertToString(Tim_MonHocTheo_MaMon(dsmh,atoi(lop->ma_mh))->ten_mh),15,2); // Doi thanh ten mon hoc
	textcenter(XMINTABLE,70,XMAXTABLE,YDAUBANG,"Nien khoa: " + convertToString(itoa(lop->khoa, tam, 10)) + " Hoc ky: " + convertToString(itoa(lop->hoc_ky, tam, 10)) + " Nhom: " + convertToString(itoa(lop->nhom, tam, 10)),1,15);
	VeDauBang(diemltc,diemSize,DiemLabelNum,XMINTABLE,YDAUBANG);

	short i = 0;
	DANG_KI *stack[slsv];
	DS_SVDK nodeChay = lop->ds_svdk;
	for (short k = 0; k < slsv; k++){
		stack[k] = &(nodeChay->data);
		nodeChay = nodeChay->next;
	}

	short y = YTABLE;
	for (short j = i; j < 10 && j < i + slsv; j++){
		VeDong(diemSize,DiemLabelNum,XMINTABLE,y,0);
		InDiemTheoDong(dssv,stack[j],j+1,XMINTABLE,y);
		y+=DONG;
	}

	short a = NhapDiem(stack[i]->diem,i,slsv,XNHAPDIEM,YTABLE+((i%10)*DONG));

	while (1){
		delay(10);
		if (a == 1){ // LEN
			if (i > 0){
				if (i % 10 == 0){
					XoaBangDuLieu();
					i--;
					y = YTABLE;
					for (short j = i-9; j <= i; j++){
						VeDong(diemSize,DiemLabelNum,XMINTABLE,y,0);
						InDiemTheoDong(dssv,stack[j],j+1,XMINTABLE,y);
						y+=DONG;
					}
					a = NhapDiem(stack[i]->diem,i,slsv,XNHAPDIEM,YTABLE+((i%10)*DONG));
				}
				else{
					i--;
					a = NhapDiem(stack[i]->diem,i,slsv,XNHAPDIEM,YTABLE+((i%10)*DONG));
				}
			}
		}
		else if (a == 2){ // XUONG
			if (i + 1 < slsv){
				if ((i + 1) % 10 == 0){
					XoaBangDuLieu();
					i++;
					short conlai = slsv - i >= 10 ? 10 : slsv - i;
					y = YTABLE;
					for (short j = i; j < i + conlai; j++){
						VeDong(diemSize,DiemLabelNum,XMINTABLE,y,0);
						InDiemTheoDong(dssv,stack[j],j+1,XMINTABLE,y);
						y+= DONG;
					}
					a = NhapDiem(stack[i]->diem,i,slsv,XNHAPDIEM,YTABLE+((i%10)*DONG));
				}
				else{
					i++;
					a = NhapDiem(stack[i]->diem,i,slsv,XNHAPDIEM,YTABLE+((i%10)*DONG));
				}
			}
		}
		else{
			XoaHDSD();
			XoaBang();
			return;
		}
	}
}
void InDiemTrungBinhTheoDong(DS_SV sv, float diemtb, short stt, short x, short y){
	char tam[5];
	outtextxy(x+5,y+12,itoa(stt,tam,10));
	x+= dtbSize[0]; outtextxy(x+5,y+12,sv->data.ma_sv);
	x+= dtbSize[1]; outtextxy(x+5,y+12,sv->data.ho);
	x+= dtbSize[2]; outtextxy(x+5,y+12,sv->data.ten);
	x+= dtbSize[3]; ftoa(diemtb,tam); outtextxy(x+5,y+12,tam);
}
void InDiem(LOP_TC *lop, DS_SV dssv, TREE dsmh){
	XoaBang();
	XoaHDSD();
	VeDauBang(diemltc,diemSize,DiemLabelNum,XMINTABLE,YDAUBANG);

	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5, 440, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5, 470, "LEN XUONG DE");
	outtextxy(xMenuChinh+5, 500, "SANG TRANG");

	short sl = DemSoLuongSVDK(lop->ds_svdk);
	char tam[10];
	char kytu;
	short stackNum = 0;
	DS_SVDK dsdk_tam[sl/10]; // MANG TAM DE LUU CAC NODE DAU CUA 1 TRANG TRONG DANH SACH
	DS_SVDK nodeChay = lop->ds_svdk;
	DS_SVDK nodeDau = nodeChay;

	textcenter(XMINTABLE,10,XMAXTABLE,70,"BANG DIEM MON HOC " + convertToString(Tim_MonHocTheo_MaMon(dsmh,atoi(lop->ma_mh))->ten_mh),15,2); // Doi thanh ten mon hoc
	textcenter(XMINTABLE,70,XMAXTABLE,YDAUBANG,"Nien khoa: " + convertToString(itoa(lop->khoa, tam, 10)) + " Hoc ky: " + convertToString(itoa(lop->hoc_ky, tam, 10)) + " Nhom: " + convertToString(itoa(lop->nhom, tam, 10)),1,15);
	
	short y = YTABLE;
	for (short j = 0; j < 10 && nodeChay != NULL; j++){ // IN CAC PHAN TU THEO 1 TRANG
		VeDong(diemSize,DiemLabelNum,XMINTABLE,y,0);
		InDiemTheoDong(dssv,&(nodeChay->data),stackNum*10+j+1,XMINTABLE,y);
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
						nodeChay = dsdk_tam[--stackNum];
						nodeDau = nodeChay;
						XoaBangDuLieu();
						y = YTABLE;
						for (short j = 0; j < 10 && nodeChay != NULL; j++){
							VeDong(diemSize,DiemLabelNum,XMINTABLE,y,0);
							InDiemTheoDong(dssv,&(nodeChay->data),stackNum*10+j+1,XMINTABLE,y);
							nodeChay = nodeChay->next;
							y+=DONG;
						}
					}
					break;
				case KEY_DOWN:
					if (nodeChay != NULL){
						dsdk_tam[stackNum++] = nodeDau;
						nodeDau = nodeChay;
						XoaBangDuLieu();
						y = YTABLE;
						for (short j = 0; j < 10 && nodeChay != NULL; j++){
							VeDong(diemSize,DiemLabelNum,XMINTABLE,y,0);
							InDiemTheoDong(dssv,&(nodeChay->data),stackNum*10+j+1,XMINTABLE,y);
							nodeChay = nodeChay->next;
							y+=DONG;
						}
					}
					break;
				case ESC:
					XoaHDSD();
					return;
			}
		}
	}
}

void ftoa(float f, char *mang){
	if (f == 0 || f == 10){
		itoa((int) f, mang, 10);
		return;
	}
	int n = (int) f;
	int tp = ((int)(f*10))%10;
	itoa(n,mang,10);
	strcat(mang,".");
	char tam[3];
	strcat(mang,itoa(tp,tam,10));
}

char* ChonMonHoc(TREE goc)
{
	int demNode=0,chon=0; //chon bien de lam vitri trong mang khi do cay ra mang ddos;
	DemNodeDuong(goc,demNode);
	if(goc==NULL || demNode ==0)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"DANH SACH MON HOC RONG.", "THONG BAO", MB_OK);
		return NULL;
	}
	TREE ds[demNode]; // de sap xep khong lam thay doi trong cay
	DoTreeRaMangConTro(goc,ds,chon);
	SapXepMonHocTheo_TenMonHoc(ds,demNode);
	// dung xong thi cho chon = 0 de dung lai
	chon=0;
	char kytu;
	short y;
	int GoTo,i,j; // i la bien de dem sl con lai de in trang tiep theo ,vitrimang de giu vitri cua phan tu trong mang truoc khi mang di xoa tren cay r quay lai xoa tren mang
	MON_HOC *mon; // tim mon hoc can xu ly trong cay
	MonHoc:
	if(demNode==0)
	{
		MessageBeep(0xFFFFFFFF);
		MessageBox(NULL,"DANH SACH MON HOC RONG.", "THONG BAO", MB_OK);
		return NULL;
	}
	// if(chon==demNode) // xoa cuoi khong in ra 1 dong rac
	// 	chon--;

	setcolor(0);
	setbkcolor(15);
	outtextxy(xMenuChinh+5,440, "F1: TIM KIEM");
	outtextxy(xMenuChinh+5,470, "DUNG MUI TEN");
	outtextxy(xMenuChinh+5,500, "LEN XUONG DE");
	outtextxy(xMenuChinh+5,530, "DI CHUYEN");

	XoaBang();
	textcenter(XMINTABLE,yMenuChinh,XMAXTABLE,YDAUBANG,"CHON MON HOC CHO LOP TIN CHI",15,2);
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
						// y = YTABLE;
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
						// y = YTABLE;
						VeDong(mhSize,MhLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),0);
						InThongTin_MotMonHoc(ds[chon]->data,XMINTABLE,YTABLE+((chon%10)*DONG));
						chon++;
						VeDong(mhSize,MhLabelNum,XMINTABLE,YTABLE+((chon%10)*DONG),2);
						InThongTin_MotMonHoc(ds[chon]->data,XMINTABLE,YTABLE+((chon%10)*DONG));
					}
					break;
				case ENTER:
					XoaBang();
					return ds[chon]->data.ma_mh;
				case KEY_F1://Tim kiem
					GoTo=ChucNangTimMonHoc(goc,mon,"TIM KIEM MON HOC");
					if(GoTo==-1)
						goto MonHoc;
					XoaHDSD();
					XoaBang();
					return mon->ma_mh;
				case ESC:
					XoaBang();
					return NULL;
			}
		}
	}
}

bool KiemTraMoTrungMonTrongMotNam(DS_LOP_TC &ds, char* mamon, short nk, short hk){
	for (short i = 0; i < ds.n_loptc; i++){
		if (KiemTraTrungChuoi(ds.ds_ltc[i]->ma_mh,mamon) && ds.ds_ltc[i]->khoa == nk && (ds.ds_ltc[i]->hoc_ky != hk && hk != 3)){
			MessageBeep(0xFFFFFFFF);
			MessageBox(NULL,"MON HOC NAY DA DUOC MO TRONG KY CHINH KHAC.", "THONG BAO", MB_OK);
			return 1;
		}
	}
	return 0;
}
