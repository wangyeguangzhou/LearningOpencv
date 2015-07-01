
// MatTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatTest.h"
#include "MatTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMatTestDlg �Ի���




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


// CMatTestDlg ��Ϣ�������

BOOL CMatTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	StartDraw=false;
	detect=NULL;
	GetControlWidth(IDC_PIC_STATIC,m_picWidth);
	GetControlHeight(IDC_PIC_STATIC,m_picHeight);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMatTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		if(!m_Image==NULL)
		{
			CClientDC clientDC(this); // ����ͻ������豸�����Ķ���   
			CRect rectPicture;
			// ��ȡͼƬ�ؼ������������Ļ����   
			m_Pic.GetWindowRect(rectPicture);
			// ��ͼƬ�ؼ������������Ļ����ת��Ϊ�丸���ڼ��Ի���Ŀͻ�������
			ScreenToClient(&rectPicture);   
			clientDC.SetStretchBltMode(COLORONCOLOR);//������ƺ�ʧ�������
			//����Ļ��ƻ���Ҫ�޸����ڸı�ͼ��Ļ��Ʊ���
			m_Image.Draw(clientDC.m_hDC,rectPicture);

		}

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMatTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMatTestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(srcimg.data)srcimg.release();
	//srcimg=imread("D:\\demo.jpg");
	srcimg=imread("D:\\more2.jpg");
	if(!srcimg.data)return ;//��ȡͼ�����
	//ȷ��ת��ǰ�����е����ݶ���uchar(0~255)����(���ǵĻ�������������)������������ʾ��(��ѧ�ߣ������Ҿ������˴���)
	//2.���ݾ����С����(CImage::Create)�µĵ�CImage��
	//CImage CI;
	if(!m_Image.IsNull())  
	{  
		m_Image.Destroy();   
	}  
	MatToCImage(srcimg,m_Image);

	m_widthScale=m_Image.GetWidth()/m_picWidth;
	m_heightScale=m_Image.GetHeight()/m_picHeight;

	//SetDlgItemText(IDC_STATIC2,"OK");//��һ���ǲ������
	Invalidate();
	//CPaintDC dc(this);  
	//CI.Draw(dc.m_hDC,0,0);//�����ĳ��dc(�����Ǵ���)��(0,0)Ϊ���  
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	StartDraw=!StartDraw;
}


void CMatTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(StartDraw)
	{
		CRect controlRect;
		GetDlgItem(IDC_PIC_STATIC)->GetWindowRect(controlRect);
		ScreenToClient(controlRect);
		if(controlRect.PtInRect(point))//�������ڻ�ͼ�ؼ����棬��ô�Ͳ���ͼ
		{
			CPoint pstatic;
	
			GetControlPos(pstatic,IDC_PIC_STATIC);//����Ҫ�޸ģ�����������Ļ�øĵ�����resize��ȥ��
	
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(StartDraw)// ����Ҫ�޸ģ�����������Ϸ�����ʱ�ᱨ��
	{
		if (GetCapture() != this)       return; 
		CRect controlRect;
		GetDlgItem(IDC_PIC_STATIC)->GetWindowRect(controlRect);
		ScreenToClient(controlRect);
		if(controlRect.PtInRect(point))//�������ڻ�ͼ�ؼ����棬��ô�Ͳ���ͼ
		{
			CPoint pstatic;
			GetControlPos(pstatic,IDC_PIC_STATIC);
			CDC *pDC = GetDlgItem(IDC_PIC_STATIC)->GetWindowDC();
			CPen pen(PS_SOLID,1,RGB(234,23,53));
			CPen *pOldPen=pDC->SelectObject(&pen);
			CBrush *pBrush=CBrush::FromHandle((HBRUSH)
			GetStockObject(NULL_BRUSH));
			CBrush *pOldBrush=pDC->SelectObject(pBrush);//����ֻ�б��ߣ������м�͸���ľ���

			CPoint tempP;
			tempP.x=point.x-pstatic.x;
			tempP.y=point.y-pstatic.y;
			pDC->Rectangle(CRect(m_ptPrev,tempP));
			/*�����ǽ�ͼ���ִ���*/
			
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

			/*��ͼ���ִ������*/
			/*���ƽ�ͼ*/
			CClientDC clientDC(this); // ����ͻ������豸�����Ķ���   
			CRect rectPicture;
			// ��ȡͼƬ�ؼ������������Ļ����   
			m_ROIPic.GetWindowRect(rectPicture);
			// ��ͼƬ�ؼ������������Ļ����ת��Ϊ�丸���ڼ��Ի���Ŀͻ�������
			ScreenToClient(&rectPicture);   
			clientDC.SetStretchBltMode(COLORONCOLOR);//������ƺ�ʧ�������
			//����Ļ��ƻ���Ҫ�޸����ڸı�ͼ��Ļ��Ʊ���
			cROI.Draw(clientDC.m_hDC,rectPicture);
			
		
	  /*			CString xs;
			CString ys;
			xs.Format("%lf",temXScale);
			ys.Format("%lf",temYScale);
			SetDlgItemText(IDC_testXSTATIC,xs);
			SetDlgItemText(IDC_testySTATIC,ys);
			BOOL temp=FALSE;
			SetDlgItemInt(IDC_CXSTATIC,abs(m_ptPrev.x-tempP.x),temp);
			SetDlgItemInt(IDC_CYSTATIC,abs(m_ptPrev.y-tempP.y),temp);//������Ϊ���Դ���
     */

			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			ReleaseDC(pDC);
			ReleaseCapture();//��һ������λ���д�����
	}
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
void CMatTestDlg::GetControlPos(CPoint &p,int nID)
{
	CRect rect;
	GetDlgItem(nID)->GetWindowRect(&rect);//��ȡ�ؼ��������Ļ��λ��
	ScreenToClient(rect);//ת��Ϊ�Ի����ϵ����λ��
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
	ROIPos.x=(int)(Pos.x*xScale);//ע�����������ת������δ���������
	ROIPos.y=(int)(Pos.y*yScale);

}
void CMatTestDlg::GetControlWidth(int nID,DOUBLE &controlWidth)
{
	CRect rect;
	GetDlgItem(nID)->GetWindowRect(&rect);//��ȡ�ؼ��������Ļ��λ��
	ScreenToClient(rect);//ת��Ϊ�Ի����ϵ����λ��
	controlWidth=rect.Width();
}
void CMatTestDlg::GetControlHeight(int nID,DOUBLE &controlHeight)
{
	CRect rect;
	GetDlgItem(nID)->GetWindowRect(&rect);//��ȡ�ؼ��������Ļ��λ��
	ScreenToClient(rect);//ת��Ϊ�Ի����ϵ����λ��
	controlHeight=rect.Height();
}


void CMatTestDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		CBrush *pOldBrush=pDC->SelectObject(pBrush);//����ֻ�б��ߣ������м�͸���ľ���

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}


void CMatTestDlg::OnBnClickedButton4()//��ʼ���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	StartDraw=false;//���ٽ��л���
	/*�����һ�α����ͼ�����*/
	imwrite("roi.jpg",ROIImage);

	//��ʵ����Ӧ�ó������һ��������ͼ�������ڶ���Щͼ����Ĳ����������������ͻᾡ������
	//����ټ���һ�����ж�detect�Ƿ��Ѿ���ָ���еĻ�������ԭ�е�Detectʵ��
	if(detect!=NULL)detect->~Detect();
	detect=new Detect(&ROIImage,&srcimg);
	detect->StartDetect();
	//�������ĵ���Ƶ�ͼ���ϡ�
    SetDlgItemInt(IDC_testySTATIC,detect->GetSrcKeyPointCount());


}

void CMatTestDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(NULL==detect)return;
	//////////////////////////////////////////////////////////////////////////
	//���ƴ�ͼ�ĵ�������
	Mat destmatdraw;
	detect->DrawDestKeyPoint(destmatdraw);
	if(destmatdraw.data)
	{
		
		CImage tempCI;
		tempCI.Destroy();
		MatToCImage(destmatdraw,tempCI);
		CClientDC clientDC(this); // ����ͻ������豸�����Ķ���   
		CRect rectPicture;
		// ��ȡͼƬ�ؼ������������Ļ����   
		m_Pic.GetWindowRect(rectPicture);
		// ��ͼƬ�ؼ������������Ļ����ת��Ϊ�丸���ڼ��Ի���Ŀͻ�������
		ScreenToClient(&rectPicture);   
		clientDC.SetStretchBltMode(COLORONCOLOR);//������ƺ�ʧ�������
		//����Ļ��ƻ���Ҫ�޸����ڸı�ͼ��Ļ��Ʊ���
		tempCI.Draw(clientDC.m_hDC,rectPicture);


	}
	//////////////////////////////////////////////////////////////////////////
	//����ROI��������
	Mat srcmatdraw;
	detect->DrawSrcKeyPoint(srcmatdraw);

	if(srcmatdraw.data)
	{
		CImage tempCI;
		tempCI.Destroy();
		MatToCImage(srcmatdraw,tempCI);
		CClientDC clientDC(this); // ����ͻ������豸�����Ķ���   
		CRect rectPicture;
		// ��ȡͼƬ�ؼ������������Ļ����   
		m_ROIPic.GetWindowRect(rectPicture);
		// ��ͼƬ�ؼ������������Ļ����ת��Ϊ�丸���ڼ��Ի���Ŀͻ�������
		ScreenToClient(&rectPicture);   
		clientDC.SetStretchBltMode(COLORONCOLOR);//������ƺ�ʧ�������
		//����Ļ��ƻ���Ҫ�޸����ڸı�ͼ��Ļ��Ʊ���
		tempCI.Draw(clientDC.m_hDC,rectPicture);
	}

}

void CMatTestDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL==detect)return;
	detect->StartMatch();
	SetDlgItemInt(IDC_CXSTATIC,detect->GetMatchesCount());
	SetDlgItemInt(IDC_resultSTATIC,detect->destRectCount);

	//����ƥ������
	CDC *pDC = GetDlgItem(IDC_PIC_STATIC)->GetWindowDC();
	CPen pen(PS_SOLID,1,RGB(234,23,53));
	CPen *pOldPen=pDC->SelectObject(&pen);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)
		GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush=pDC->SelectObject(pBrush);//����ֻ�б��ߣ������м�͸���ľ���
   for(std::vector<CRect>::iterator it=detect->destRects.begin();it!=detect->destRects.end();it++)
   {
	pDC->Rectangle(*it);
   }
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	ReleaseDC(pDC);
}
