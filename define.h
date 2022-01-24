#define ENTER 13
#define ESC 27
#define BACKSPACE 8


#define FONTSIZE 16
#define BUTTONWIDTH 250
#define BUTTONHEIGHT 60 
#define MAXWIDTH 1515
#define MAXHEIGHT 720
#define MAXWIDTHTABLE 1500
#define MAXHEIGHTTABLE 700
#define MINWIDTHTABLE 5
#define MINHEIGHTTABLE 5
#define BGCOLOR 15
#define DONG 40
#define XMINTABLE 280
#define XMAXTABLE 1480
#define YDAUBANG 150
#define YTABLE 190
#define YMAXMENU 310
#define xMenuChinh 10
#define yMenuChinh 10
#define XMINBANGTHEM 400
#define YMINBANGTHEM 100
#define XMAXBANGTHEM 1400
#define YMAXBANGTHEM 550
#define YMAXBANGTIMKIEM 250
#define XBANGNHAP 610
#define YBANGNHAP 160
#define XNHAPDIEM 1280
#define XMAXNHAPDIEM 1480

#define menuChinhItem 4
#define menuLtcItem 4
#define menuSinhVienItem 4
#define menuMonHocItem 3
#define menuDiemItem 3
#define LtcLabelNum 8
#define SvLabelNum 6
#define MhLabelNum 4
#define DkmLabelNum 5
#define DsdkLabelNum 6
#define DiemLabelNum 5
#define chonLopNum 3
#define TABLELTCNUM2 9
#define TABLELTCNUM 5
#define TABLEDKNUM 7
#define dtb_sl 5

const string menuChinh[menuChinhItem] = {"LOP TIN CHI", "SINH VIEN", "MON HOC", "DIEM"};
const string menuLopTinChi[menuLtcItem] = {"THEM LOP TC", "SUA-XOA LOP TC", "HUY LOP TC", "DSSV LOP TC"};
const string menuSinhVien[menuSinhVienItem] = {"THEM SV", "SUA-XOA SV", "DANG KY MON", "DSSV MOT LOP"};
const string menuMonHoc[menuMonHocItem] = {"THEM MON", "SUA-XOA MON", "DS MON HOC"};
const string menuDiem[menuDiemItem] = {"NHAP DIEM", "B.DIEM MON HOC", "DIEM TRUNG BINH"};
const string lopTinChiLabel[LtcLabelNum] = {"MA LOP", "MA MON", "KHOA", "HOC KY", "NHOM", "SV MIN", "SV MAX", "T.THAI"};
const string sinhVienLabel[SvLabelNum] = {"MA LOP","MA SV", "HO", "TEN", "PHAI", "SDT"};
const string SINHVIENLABEL2[SvLabelNum-1]={"MA SV", "HO", "TEN", "PHAI", "SDT"};
const string monHocLabel[MhLabelNum] = {"MA MON", "TEN MON", "STCLT", "STCTH"};
const string dangKyMonLabel[DkmLabelNum] = {"MA MON", "TEN MON", "NHOM", "DA DK", "C.LAI"};
const string dsdk[DsdkLabelNum] = {"MA SV", "HO", "TEN", "PHAI", "SDT", "MA LOP"};
const string diemltc[DiemLabelNum] = {"STT", "MA SV", "HO", "TEN", "DIEM"};
const string chonLop[chonLopNum] = {"STT","TEN LOP","SL SINH VIEN"};
const string dtb[dtb_sl] = {"STT", "MASV", "HO", "TEN", "DIEM TB"};
const string TABLELTC2[TABLELTCNUM2]  = {"STT", "MA LOP", "MA MON", "KHOA", "HOC KY", "NHOM", "SV MIN", "SV MAX", "T.THAI"};
const string TABLELTC[TABLELTCNUM] = {"MA LOP", "MA MON", "TEN MON", "NK/HK", "NHOM"};
const string TABLEDK[TABLEDKNUM] = {"STT", "MA SV", "HO", "TEN", "PHAI", "SDT", "MA LOP"};


const short ltcSize[LtcLabelNum] = {200, 250, 150, 100, 100, 150, 150, 100};
const short mhSize[MhLabelNum] = {150, 850, 100, 100};
const short dsdkSize[DsdkLabelNum] = {200, 350, 150, 100, 200, 200};
const short svSize[SvLabelNum] = {200, 200, 350, 150, 100,200};
const short SVSIZE2[SvLabelNum-1]={200,550,150,100,200};
const short dkmSize[DkmLabelNum] = {150, 750, 100, 100, 100};
const short diemSize[DiemLabelNum] = {100, 200, 500, 200, 200};
const short chonLopSize[chonLopNum] = {100,900,200};
const short dtbSize[dtb_sl] = {100, 200, 600, 150, 150};
const short TABLELTCSIZE2[TABLELTCNUM2] = {100, 150, 250, 100, 100, 100, 150, 150, 100};
const short TABLELTCSIZE[TABLELTCNUM] = {110,110,770,110,100};
const short TABLEDKSIZE[TABLEDKNUM] = {80, 180, 350, 150, 100, 170,170};
