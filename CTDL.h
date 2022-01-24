#include <string>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <math.h>

#define MAX_LOP 10000
using namespace std;
//============= Môn ===========
struct MON_HOC
{
    //data
    char ma_mh[12];        // 9 kí t?
    char ten_mh[52];       // 49 kí t?
    unsigned short stc_lt; // 1 kí t? vd 0, 1 , 2 ,...
    unsigned short stc_th; // 1 kí t? vd 0, 1 , 2 ,...
};

struct NODE_MH
{
    MON_HOC data;
    NODE_MH *L = NULL; // con tr? Trái cây
    NODE_MH *R = NULL; // con tr? Ph?i cây
};
typedef struct NODE_MH *TREE;

//============= SINH VIÊN ==========

struct SINH_VIEN
{
    char ma_sv[17];     // 14 kí t?
    char ho[32];          // 50 kí t?
    char ten[12];         // 10 kí t?
    char gioi_tinh[5];   // 3 kí t? nam ho?c n?
    char sdt[12];         // 10 s?
    char ma_lop_sv[17]; // 14 kí t?
};

struct NODE_SV
{
    SINH_VIEN data;
    NODE_SV *next;
};
typedef struct NODE_SV* DS_SV;
// =========== ÐANG KÍ L?P TÍN CH? ========
struct DANG_KI
{
    char ma_sv[17];
    float diem; // 3 kí t? vd  8.75 , 10 , ...
};

struct NODE_DK
{
    DANG_KI data;
    NODE_DK *next;
};
typedef struct NODE_DK* DS_SVDK;
// typedef struct ds_dk// sai
// {
//     ds_dk*head=NULL;
// }danhSach_dk;
//============ L?P ==========

struct LOP_TC
{
    unsigned int ma_lop_tc; // so nguyen duong t? d?ng tang
    char ma_mh[12];
    unsigned short khoa;          // 4 s? vd : 2021
    unsigned short hoc_ky; // 1 s? vd : 1 , 2 , 3 ,...
    unsigned short nhom;   // 2 s? vd 1 , 10 , ...
    unsigned short sv_min; // 3 s?
    unsigned short sv_max; // 3 s?
    bool trang_thai;      // true ho?c false
    //con tr? danh sách sinh viên dang kí
    DS_SVDK ds_svdk = NULL;
};

struct DS_LOP_TC
{
    LOP_TC *ds_ltc[MAX_LOP];
    unsigned int n_loptc;
};
