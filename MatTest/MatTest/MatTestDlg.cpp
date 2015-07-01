
// MatTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MatTest.h"
#include "MatTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMatTestDlg 对话框




CMatTestDlg::CMatTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMatTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_STATIC, m_Pic);
	DDX_Control(pDX, IDC_ROI_STATIC, m_ROIPic);
}

BEGIN_MESSAGE_MAP(CMatTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMatTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMatTestDlg::OnBnClickedButton2)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON3, &CMatTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMatTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMatTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMatTestDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMatTestDlg 消息处理程序

BOOL CMatTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	StartDraw=false;
	detect=NULL;
	GetControlWidth(IDC_PIC_STATIC,m_picWidth);
	GetControlHeight(IDC_PIC_STATIC,m_picHeight);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMatTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMatTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		if(!m_Image==NULL)
		{
			CClientDC clientDC(this); // 构造客户区的设备上下文对象   
			CRect rectPicture;
			// 获取图片控件矩形区域的屏幕坐标   
			m_Pic.GetWindowRect(rectPicture);
			// 将图片控件矩形区域的屏幕坐标转换为其父窗口即对话框的客户区坐标
			ScreenToClient(&rectPicture);   
			clientDC.SetStretchBltMode(COLORONCOLOR);//解决绘制后失真的问题
			//下面的绘制还需要修改以期改变图像的绘制比例
			m_Image.Draw(clientDC.m_hDC,rectPicture);

		}

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMatTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMatTestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(srcimg.data)srcimg.release();
	//srcimg=imread("D:\\demo.jpg");
	srcimg=imread("D:\\more2.jpg");
	if(!srcimg.data)return ;//读取图像错误
	//确保转换前矩阵中的数据都是uchar(0~255)类型(不是的话量化到此区间)，这样才能显示。(初学者，包括我经常忘了此事)
	//2.根据矩阵大小创建(CImage::Create)新的的CImage类
	//CImage CI;
	if(!m_Image.IsNull())  
	{  
		m_Image.Destroy();   
	}  
	MatToCImage(srcimg,m_Image);

	m_widthScale=m_Image.GetWidth()/m_picWidth;
	m_heightScale=m_Image.GetHeight()/m_picHeight;

	//SetDlgItemText(IDC_STATIC2,"OK");//这一条是测试语句
	Invalidate();
	//CPaintDC dc(this);  
	//CI.Draw(dc.m_hDC,0,0);//这个以某个dc(可以是窗口)的(0,0)为起点  
}
void CMatTestDlg::MatToCImage( Mat &mat, CImage &cImage)  
{  
	//create new CImage  
	int width    = mat.cols;  
	int height   = mat.rows;  
	int channels = mat.channels();  

	cImage.Destroy(); //clear  
	cImage.Create(width,   
		height, //positive: left-bottom-up   or negative: left-top-down  
		8*channels ); //numbers of bits per pixel  

	//copy values  
	uchar* ps;  
	uchar* pimg = (uchar*)cImage.GetBits(); //A pointer to the bitmap buffer  

	//The pitch is the distance, in bytes. represent the beginning of   
	// one bitmap line and the beginning of the next bitmap line  
	int step = cImage.GetPitch();  

	for (int i = 0; i < height; ++i)  
	{  
		ps = (mat.ptr<uchar>(i));  
		for ( int j = 0; j < width; ++j )  
		{  
			if ( channels == 1 ) //gray  
			{  
				*(pimg + i*step + j) = ps[j];  
			}  
			else if ( channels == 3 ) //color  
			{  
				for (int k = 0 ; k < 3; ++k )  
				{  
					*(pimg + i*step + j*3 + k ) = ps[j*3 + k];  
				}             
			}  
		}     
	}  

} 

void CMatTestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	StartDraw=!StartDraw;
}


void CMatTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(StartDraw)
	{
		CRect controlRect;
		GetDlgItem(IDC_PIC_STATIC)->GetWindowRect(controlRect);
		ScreenToClient(controlRect);
		if(controlRect.PtInRect(point))//如果起点在绘图控件外面，那么就不画图
		{
			CPoint pstatic;
	
			GetControlPos(pstatic,IDC_PIC_STATIC);//后面要修改，把这个参数的获得改到窗口resize中去，
	
			//m_ptOrigin=point;
			m_ptPrev.x=point.x-pstatic.x;
			m_ptPrev.y=point.y-pstatic.y;
			m_ptOld.x=point.x-pstatic.x;
			m_ptOld.y=point.y-pstatic.y;
			/*m_ptOrigin.x=point.x-pstatic.x;
			m_ptOrigin.y=point.y-pstatic.y;*/
			SetCapture();
		}
	CDialogEx::OnLButtonDown(nFlags, point);
	}
}


void CMatTestDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(StartDraw)// 还需要修改，在鼠标往左上方滑动时会报错
	{
		if (GetCapture() != this)       return; 
		CRect controlRect;
		GetDlgItem(IDC_PIC_STATIC)->GetWindowRect(controlRect);
		ScreenToClient(controlRect);
		if(controlRect.PtInRect(point))//如果起点在绘图控件外面，那么就不画图
		{
			CPoint pstatic;
			GetControlPos(pstatic,IDC_PIC_STATIC);
			CDC *pDC = GetDlgItem(IDC_PIC_STATIC)->GetWindowDC();
			CPen pen(PS_SOLID,1,RGB(234,23,53));
			CPen *pOldPen=pDC->SelectObject(&pen);
			CBrush *pBrush=CBrush::FromHandle((HBRUSH)
			GetStockObject(NULL_BRUSH));
			CBrush *pOldBrush=pDC->SelectObject(pBrush);//绘制只有边线，但是中间透明的矩形

			CPoint tempP;
			tempP.x=point.x-pstatic.x;
			tempP.y=point.y-pstatic.y;
			pDC->Rectangle(CRect(m_ptPrev,tempP));
			/*下面是截图部分代码*/
			
	         if(ROIImage.data)ROIImage.release();
			 DOUBLE temXScale;
			 DOUBLE temYScale;
			 GetScale(srcimg.cols,srcimg.rows,controlRect.Width(),controlRect.Height(),temXScale,temYScale);
			 CPoint ROIPos;
			 GetROIPos(temXScale,temYScale,m_ptPrev,ROIPos);

			int ROIWidth;
			int ROIHeight;
			GetROIWidth(temXScale,(m_ptPrev.x-tempP.x),ROIWidth);
			GetROIHeight(temYScale,(m_ptPrev.y-tempP.y),ROIHeight);
			srcimg(Rect(ROIPos.x,ROIPos.y,ROIWidth,ROIHeight)).copyTo(ROIImage);

			CImage cROI;
			cROI.Destroy();
			MatToCImage(ROIImage,cROI);

			/*截图部分代码结束*/
			/*绘制截图*/
			CClientDC clientDC(this); // 构造客户区的设备上下文对象   
			CRect rectPicture;
			// 获取图片控件矩形区域的屏幕坐标   
			m_ROIPic.GetWindowRect(rectPicture);
			// 将图片控件矩形区域的屏幕坐标转换为其父窗口即对话框的客户区坐标
			ScreenToClient(&rectPicture);   
			clientDC.SetStretchBltMode(COLORONCOLOR);//解决绘制后失真的问题
			//下面的绘制还需要修改以期改变图像的绘制比例
			cROI.Draw(clientDC.m_hDC,rectPicture);
			
		
	  /*			CString xs;
			CString ys;
			xs.Format("%lf",temXScale);
			ys.Format("%lf",temYScale);
			SetDlgItemText(IDC_testXSTATIC,xs);
			SetDlgItemText(IDC_testySTATIC,ys);
			BOOL temp=FALSE;
			SetDlgItemInt(IDC_CXSTATIC,abs(m_ptPrev.x-tempP.x),temp);
			SetDlgItemInt(IDC_CYSTATIC,abs(m_ptPrev.y-tempP.y),temp);//这三行为测试代码
     */

			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			ReleaseDC(pDC);
			ReleaseCapture();//这一句代码的位置有待测试
	}
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
void CMatTestDlg::GetControlPos(CPoint &p,int nID)
{
	CRect rect;
	GetDlgItem(nID)->GetWindowRect(&rect);//获取控件相对于屏幕的位置
	ScreenToClient(rect);//转化为对话框上的相对位置
	p.x=rect.left;
	p.y=rect.top;
}
void CMatTestDlg::GetScale(int srcWidth,int srcHeight,int controlWidth,int controlHeight,DOUBLE &xScale,DOUBLE &yScale)
{
	xScale=(DOUBLE)srcWidth/(DOUBLE)controlWidth;
	yScale=(DOUBLE)srcHeight/(DOUBLE)controlHeight;
}
void CMatTestDlg::GetROIWidth(DOUBLE xScale,int thumbWidth,int &ROIWidth)
{
	ROIWidth=abs((int)(xScale*thumbWidth));

}
void CMatTestDlg::GetROIHeight(DOUBLE yScale,int thumbHeight,int &ROIHeight)
{
	ROIHeight=abs((int)(yScale*thumbHeight));

}
void CMatTestDlg::GetROIPos(DOUBLE xScale,DOUBLE yScale,CPoint &Pos,CPoint &ROIPos)
{
	ROIPos.x=(int)(Pos.x*xScale);//注意这里的坐标转换，这段代码有问题
	ROIPos.y=(int)(Pos.y*yScale);

}
void CMatTestDlg::GetControlWidth(int nID,DOUBLE &controlWidth)
{
	CRect rect;
	GetDlgItem(nID)->GetWindowRect(&rect);//获取控件相对于屏幕的位置
	ScreenToClient(rect);//转化为对话框上的相对位置
	controlWidth=rect.Width();
}
void CMatTestDlg::GetControlHeight(int nID,DOUBLE &controlHeight)
{
	CRect rect;
	GetDlgItem(nID)->GetWindowRect(&rect);//获取控件相对于屏幕的位置
	ScreenToClient(rect);//转化为对话框上的相对位置
	controlHeight=rect.Height();
}


void CMatTestDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(StartDraw)
	{
		if(GetCapture()!=this)return ;
		CPoint pstatic;
		GetControlPos(pstatic,IDC_PIC_STATIC);
		int oldMode;
		CDC *pDC = GetDlgItem(IDC_PIC_STATIC)->GetWindowDC();
		oldMode = pDC->GetROP2();

		pDC->SetROP2(R2_NOT);  

		//  pDC->MoveTo(m_ptPrev);
		//pDC->LineTo(m_ptOld);
		CPen pen(PS_SOLID,1,RGB(234,23,53));
		CPen *pOldPen=pDC->SelectObject(&pen);
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)
			GetStockObject(NULL_BRUSH));
		CBrush *pOldBrush=pDC->SelectObject(pBrush);//绘制只有边线，但是中间透明的矩形

		pDC->Rectangle(CRect(m_ptPrev,m_ptOld));	
		/*  pDC->MoveTo(m_ptPrev);
		pDC->LineTo(point.x-pstatic.x,point.y-pstatic.y);*/
		CPoint tempP;
		tempP.x=point.x-pstatic.x;
		tempP.y=point.y-pstatic.y;
		pDC->Rectangle(CRect(m_ptPrev,tempP));

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		
		    pDC->SetROP2(oldMode);   
		    m_ptOld.x = point.x-pstatic.x;
			m_ptOld.y=point.y-pstatic.y;
		    ReleaseDC(pDC);

	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMatTestDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void CMatTestDlg::OnBnClickedButton4()//开始检测
{
	// TODO: 在此添加控件通知处理程序代码
	StartDraw=false;//不再进行绘制
	/*用最后一次保存的图像进行*/
	imwrite("roi.jpg",ROIImage);

	//其实这里应该抽象出来一个单独的图像类用于对这些图像处理的操作，这样界面代码就会尽量简练
	//最好再加上一句来判断detect是否已经有指向，有的话就销毁原有的Detect实例
	if(detect!=NULL)detect->~Detect();
	detect=new Detect(&ROIImage,&srcimg);
	detect->StartDetect();
	//将检测出的点绘制到图像上。
    SetDlgItemInt(IDC_testySTATIC,detect->GetSrcKeyPointCount());


}

void CMatTestDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if(NULL==detect)return;
	//////////////////////////////////////////////////////////////////////////
	//绘制大图的的特征点
	Mat destmatdraw;
	detect->DrawDestKeyPoint(destmatdraw);
	if(destmatdraw.data)
	{
		
		CImage tempCI;
		tempCI.Destroy();
		MatToCImage(destmatdraw,tempCI);
		CClientDC clientDC(this); // 构造客户区的设备上下文对象   
		CRect rectPicture;
		// 获取图片控件矩形区域的屏幕坐标   
		m_Pic.GetWindowRect(rectPicture);
		// 将图片控件矩形区域的屏幕坐标转换为其父窗口即对话框的客户区坐标
		ScreenToClient(&rectPicture);   
		clientDC.SetStretchBltMode(COLORONCOLOR);//解决绘制后失真的问题
		//下面的绘制还需要修改以期改变图像的绘制比例
		tempCI.Draw(clientDC.m_hDC,rectPicture);


	}
	//////////////////////////////////////////////////////////////////////////
	//绘制ROI的特征点
	Mat srcmatdraw;
	detect->DrawSrcKeyPoint(srcmatdraw);

	if(srcmatdraw.data)
	{
		CImage tempCI;
		tempCI.Destroy();
		MatToCImage(srcmatdraw,tempCI);
		CClientDC clientDC(this); // 构造客户区的设备上下文对象   
		CRect rectPicture;
		// 获取图片控件矩形区域的屏幕坐标   
		m_ROIPic.GetWindowRect(rectPicture);
		// 将图片控件矩形区域的屏幕坐标转换为其父窗口即对话框的客户区坐标
		ScreenToClient(&rectPicture);   
		clientDC.SetStretchBltMode(COLORONCOLOR);//解决绘制后失真的问题
		//下面的绘制还需要修改以期改变图像的绘制比例
		tempCI.Draw(clientDC.m_hDC,rectPicture);
	}

}

void CMatTestDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL==detect)return;
	detect->StartMatch();
	SetDlgItemInt(IDC_CXSTATIC,detect->GetMatchesCount());
	SetDlgItemInt(IDC_resultSTATIC,detect->destRectCount);

	//画出匹配区域
	CDC *pDC = GetDlgItem(IDC_PIC_STATIC)->GetWindowDC();
	CPen pen(PS_SOLID,1,RGB(234,23,53));
	CPen *pOldPen=pDC->SelectObject(&pen);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)
		GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush=pDC->SelectObject(pBrush);//绘制只有边线，但是中间透明的矩形
   for(std::vector<CRect>::iterator it=detect->destRects.begin();it!=detect->destRects.end();it++)
   {
	pDC->Rectangle(*it);
   }
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	ReleaseDC(pDC);
}
