//******************************************CAC HAM DO HOA******************************************
void disableX();
void setup();
void HideConsole();
void normal();
void highlight();
void normalTable();
void highlightTable(); // Dung de hien thi cac mon da dang ky
void selectTable(); // Ve thanh sang trong chuc nang dang ky mon
void textcenter(short x1, short y1, short x2, short y2, string str, int textcolor, int bgtextcolor); // CAN GIUA TEXT
void VeNutMenu(short x, short y, string str);
void VeMenu(const string str[], short menuItem);


void MenuChinhDong(DS_LOP_TC &dsltc, DS_SV dssv, TREE &dsmh, short chon);
void MenuLtcDong(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh, short chon);
void MenuSvDong(DS_LOP_TC &dsltc, DS_SV &dssv, TREE dsmh, short chon);
void MenuMhDong(DS_LOP_TC &dsltc, TREE &dsmh, short chon);
void MenuDiemDong(DS_LOP_TC &dsltc, DS_SV dssv, TREE dsmh, short chon);


void VeBangThem(string main, const string* label, short soLuong); // VE BANG THEM MOT DOI TUONG (LOP TIN CHI, SINH VIEN, MON HOC)
void VeBangNhap(string main, string label); // DUNG DE HIEN THI NHAP TIM KIEM THEO MA
void VeDauBang(const string* title, const short* doRongCot, short soLuongCot, short x, short y); // Ve cac title cua bang
void VeDong(const short* doRongCot, short soLuongCot, short x, short y, short highlight);
void tao_label(int x1, int y1, int x2, int y2, int mau_nen, int mau_chu, string label);
void tao_input(int x1, int y1, int x2, int y2);

void xoa_input(int x1, int y1);
void XoaMenu();
void XoaBang();
void XoaBangDuLieu();
void XoaHDSD();
void XoaAll();
void XoaDiem(short y);

//**************************************************************************************************
// =================================== PHAN XU LY LOP TIN CHI VA DIEM ==============================
//====================================              START                  =========================
void InLtcTheoDong(LOP_TC* lop, short stt, short x, short y);
void InLtcTheoDong(LOP_TC* lop, TREE dsmh, short x, short y);
void InDsdkTheoDong(DS_SV dssv, char* ma, short stt, short x, short y);
void InDangKyMonTheoDong(LOP_TC* lop, TREE dsmh, short sl, short x, short y); // IN LOP TIN CHI DE DANG KY MON THEO MOT DONG
void InThongTinLTC(LOP_TC* lop); // IN THONG TIN CUA MOT LOP TIN CHI DE XEM
void InDanhSachDangKy(LOP_TC* lop, DS_SV dssv); // IN DANH SACH SVDK CUA MOT LOP TIN CHI
void InDiemTheoDong(DS_SV dssv, DANG_KI* sv, short stt, short x, short y);
void InDiemTrungBinhTheoDong(DS_SV sv, float diemtb, short stt, short x, short y);
void InDiem(LOP_TC* lop, DS_SV dssv, TREE dsmh);
void SelectLopTinChi(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh); // SUA VA XOA
void InDsdkLopTinChi(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh);
void InDiemLopTinChi(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh);
void InDiemTrungBinh(DS_LOP_TC ds, DS_SV dssv, TREE dsmh);


//******************************************CHUC NANG CHINH******************************************
void KhoiTaoLopTinChi(LOP_TC* lop);
void KhoiTaoNodeDangKy(DS_SVDK sv);
void ThemLopTinChi(DS_LOP_TC &ds, TREE dsmh);
void SuaLopTinChi(DS_LOP_TC &ds, TREE dsmh, short vitri);
void XoaLopTinChi(DS_LOP_TC &ds, short vitri);
short TimKiemLopTinChi(DS_LOP_TC ds, unsigned int maLop);
short TimKiemLopTinChi(LOP_TC* mang[], short sl, unsigned maLop);
void GiaiPhongDanhSachDangKy(DS_SVDK &ds);
void GiaiPhongDSLTC(DS_LOP_TC &ds);
void DangKyLopTinChi(DS_LOP_TC &dsltc, DS_SV dssv, TREE dsmh);
int DemSoLuongSVDK(DS_SVDK ds);
void ThemVaoDSDK(LOP_TC* lop, DS_SVDK ref);
void XoaSvTrongDSDK(DS_SVDK &ds, char* mssv);
void HuyLopTinChi(LOP_TC* lop);
void AutoHuyLopTinChi(DS_LOP_TC &ds);
void ChucNangNhapDiem(DS_LOP_TC &ds, DS_SV dssv, TREE dsmh);
float TinhDiemTrungBinhSv(DS_LOP_TC &ds, TREE dsmh, char* masv);
void NhapDiemChoLopTinChi(LOP_TC* lop, short slsv, DS_SV dssv, TREE dsmh);
char* ChonMonHoc(TREE goc);

//=====================================					END				=============================
//===================================== 	PHAN XU LY LOP TIN CHI		=============================
//***************************************************************************************************


//*************************************		CAC HAM PHU TRO				*****************************
string convertToString(char* a);
bool DocFileLopTinChi(DS_LOP_TC &ds);
bool GhiFileLopTinChi(DS_LOP_TC ds);
void NhapMa(char* mang, short soLuongKyTu, bool kieuDuLieu, short x, short y);
void NhapNienKhoa(unsigned short &so, short x, short y);
void NhapHocKy(unsigned short &so, short x, short y);
void NhapNhom(unsigned short &so, short x, short y);
void NhapSoLuongSV(unsigned short &so, short x, short y);
short NhapDiem(float &diem, short chon, short sl, short x, short y);
bool KiemTraTrungChuoi(char* chuoi1, char* chuoi2);
bool KiemTraTrungLTC(DS_LOP_TC ds, char* ma_mh, unsigned short nienkhoa, unsigned short hocky, unsigned short nhom);
bool KiemTraDaDangKy(DS_SVDK ds, char* mssv);
bool KiemTraDangKyTrungMon(LOP_TC *mang[], short soLuong, bool* ttdk, bool* thaydoi, short chon);
bool KiemTraDaCoDiem(LOP_TC *lop);
void swap(LOP_TC* &a, LOP_TC* &b);
void swapBool(bool &a, bool &b);
void swapShort(short &a, short &b);
bool SoSanhLopTinChi(LOP_TC* index, LOP_TC* pivot);
bool SoSanhTheoTenVaMaMon(TREE dsmh, LOP_TC* index, LOP_TC* pivot);
int partitionTichHop(DS_LOP_TC &ds, short low, short high);
int partitionTheoTenMon(DS_LOP_TC &ds, TREE dsmh, short low, short high);
int partitionTheoTenMon(LOP_TC* mang[], bool* ttdk, bool* thaydoi, short* slsv, TREE dsmh, short low, short high);
void QuickSortTheoTenMon(DS_LOP_TC &ds, TREE dsmh, short low, short high);
void QuickSortTichHop(DS_LOP_TC &ds, short low, short high);
void QuickSortTheoTenMon(LOP_TC* mang[], bool* ttdk, bool* thaydoi, short* slsv, TREE dsmh, short low, short high);

//********************************			PHU TRO NHAP MON HOC	***********************************
void Nhap_Ho_SV(char *ma, unsigned short soLuongKyTu, short x, short y);
void Nhap_Ten_SV(char *ma, unsigned short soLuongKyTu, short x, short y);
void Nhap_Gioi_Tinh(char *ma, unsigned short soLuongKyTu, short x, short y);
void NhapTinChi(unsigned short &so, short x, short y);
void Nhap_SDT(char *ma,unsigned short soLuongKyTu, short x, short y);

//****************************************************************************************************
// =================================== 			PHAN XU LY MON HOC	  ================================
//====================================              START                  ===========================
MON_HOC khoi_taoMH(MON_HOC &mon);
TREE Tao_NODE_MonHoc(MON_HOC &mon);
int TimNodeAm(TREE &goc);
void LayGiaTriTrai(TREE &t, int& x1, int& x2);
int Lay_Ma_MonHoc(TREE t, int n,int &chieuCao,int &tongNode ,int &viTriLa);
void XoaMonHocGiaiPhong(TREE &goc, int mamon ); // moi
MON_HOC* Tim_MonHocTheo_MaMon(TREE &goc,int maMon);
void ChucNang_ThemMonHoc(TREE &goc,int &chieuCao,int &tongNode );
void DoTreeRaMangConTro(TREE t, TREE ds[], int &n_ds);
void swapDataMH(MON_HOC &a,MON_HOC &b);
void SapXepMonHocTheo_TenMonHoc(TREE ds[], int &n_ds);
void InThongTin_MotMonHoc(MON_HOC mon,short x,short y);
void In_DsMonHoc(TREE &goc);
void DemNodeDuong(TREE &goc,int &dem);

void SelectMonHoc(DS_LOP_TC &dsltc,TREE &goc ); // moi
int ChucNangSuaMonHoc(DS_LOP_TC dsltc,TREE &goc,MON_HOC *&mon); 
int ChucNangXoaMonHoc(DS_LOP_TC &dsltc,TREE &goc,TREE ds[],MON_HOC *&mon ,int &demNode,int &viTriMang); // moi
int ChucNangTimMonHoc(TREE &goc,MON_HOC *&mon,string ThongBao);
void InThongTinMonHoc(MON_HOC *mon,string ThongBao);
void SuaThongTinTrenMang(TREE ds[],int &demNode,int &viTriMang); // moi
//========== Doc - Ghi file TXT
void Doc_FILE_MonHoc(TREE &t);
void Ghi_FILE_NLR(ofstream &file, TREE t);
void Ghi_FILE_MonHoc(TREE &t);
bool is_empty(ifstream& pFile);
void Doc_FILE_Num(int &chieuCao,int &tongNode );
void Ghi_FILE_num(int &chieuCao,int &tongNode );

//****************************************************************************************************
// =================================== 			     END	               ===========================
//====================================          PHAN XU LY MON HOC         ===========================





//****************************************************************************************************
// =================================== 			PHAN XU LY SINH VIEN	  ============================
//====================================              START                  ===========================

SINH_VIEN Khoi_tao_SV(SINH_VIEN &sv);
NODE_SV *Tao_Node_SV(SINH_VIEN &sv);
bool Check_maSV_TrongDSSV(DS_SV &head_ds, char *ma);
NODE_SV *Check_maSV_TrongDSSV1(DS_SV &head_ds, char *ma); // không tồn tại : NULL / tồn tại :NODE_SV*

void Them_NodeSV_Vao_DS(DS_SV &head_ds, SINH_VIEN &sv);
void Chuc_Nang_Them_SV_Theo_LOP(DS_SV &head_ds);

void Xoa_NODE_SV_Theo_maSV(DS_SV &head_ds, char *ma);
void Doc_FILE_DSSV(DS_SV &head_ds);
void Ghi_FILE_DSSV(DS_SV &head_ds);

void InLopSVTheoDong(char *maLop,unsigned int &sl,short stt,short x,short y);
void InSvTheoDong1(SINH_VIEN sv, short x, short y);
void in_DsLopSV(DS_SV &head_ds);
void InSvTheoDong(SINH_VIEN sv, short x, short y);
void SelectSV(DS_LOP_TC &dsltc,DS_SV &head_ds);

int KiemTra_SVCoDiemChua(DS_SVDK &head_ds,char *maSV);
void Xoa_NODE_DK(DS_SVDK &head_ds, char *ma);
void Sua_Tren_DSSVDK(DS_LOP_TC &ds,char *maSV_Cu,char *maSV_Moi);
int ChucNangTimSV(DS_SV &head_ds,SINH_VIEN *&sv,string ThongBao);
int ChucNangLocMonTheoTen(TREE ds[],int &demNode,string ThongBao);
int ChucNangLocSV(DS_SV &head_ds,SINH_VIEN *arrDSSV[],string ThongBao,int &demSV);

void InThongTinSV(SINH_VIEN *sv);
int ChucNangSuaInfoSV(DS_LOP_TC &dsltc,DS_SV &head_ds,SINH_VIEN *ds[],SINH_VIEN &sv,int demSV);
void SuaSVTrenMang(SINH_VIEN *ds[],char *maSVcu,SINH_VIEN sv,int demSV);
bool ChucNangXoaSV(DS_LOP_TC &dsltc,DS_SV &head_ds,SINH_VIEN *dssv[],SINH_VIEN sv,int &demSV); // moi cho chon;
void ftoa(float f, char *mang);
//****************************************************************************************************
// =================================== 			     END	               ===========================
//====================================          PHAN XU LY SINH VIEN         =========================


