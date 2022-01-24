#include <winbgim.h>
#include "CTDL.h"
#include "define.h"
#include "NguyenMauHam.h"
#include "XuLyLopTinChi.h"
#include "XuLyNhapXuat.h"
#include "XuLyMonHoc.h"
#include "XuLySinhVien.h"

//********************SON**********************

int main()
{	
	DS_LOP_TC dsltc;
	dsltc.n_loptc = 0;
	DS_SV dssv = NULL;
	TREE dsmh = NULL;
	
	setup();
	Doc_FILE_MonHoc(dsmh);
	DocFileLopTinChi(dsltc);
	Doc_FILE_DSSV(dssv);
	MenuChinhDong(dsltc,dssv,dsmh,0);
	while (!kbhit()) delay(1);
	return 0;
}
