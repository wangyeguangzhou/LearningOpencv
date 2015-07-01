
// MatTestDlg.h : 头文件
//

#pragma once
//#include <opencv2/core/core.hpp>  
//#include<opencv2/highgui/highgui.hpp>  
#include "afxwin.h"
#include "Detect.h"

#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include "opencv2/features2d/features2d.hpp"
#include<opencv2/legacy/legacy.hpp>

using namespace cv;  

// CMatTestDlg 对话框
class CMatTestDlg : public CDialogEx
{
// 构造
public:
	CMatTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MATTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();


	void MatToCImage( Mat &mat, CImage &cImage);
	void GetControlPos(CPoint &p,int nID);
	void GetControlWidth(int nID,DOUBLE &controlWidth);
	void GetControlHeight(int nID,DOUBLE &controlHeight);
	void GetScale(int srcWidth,int srcHeight,int controlWidth,int controlHeight,DOUBLE &xScale,DOUBLE &yScale);
	void GetROIWidth(DOUBLE xScale,int thumbWidth,int &ROIWidth);
	void GetROIHeight(DOUBLE yScale,int thumbHeight,int &ROIHeight);
	void GetROIPos(DOUBLE xScale,DOUBLE yScale,CPoint &Pos,CPoint &ROIPos);
	//void StartDetect(Mat srcImage ,Mat  destImage,std::vector<KeyPoint> keyPointSrc,std::vector<KeyPoint> keyPointsDest);
	afx_msg void OnBnClickedButton2();
private:
	CPoint m_ptOrigin;
	CPoint m_ptPrev;
    CPoint m_ptOld;
	BOOL StartDraw; 
	DOUBLE m_picWidth;
	DOUBLE m_picHeight;
	DOUBLE m_widthScale;
	DOUBLE m_heightScale;
	CStatic m_Pic;
	CImage m_Image;
	Mat ROIImage;
	Mat srcimg;
	Detect *detect;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
	CStatic m_ROIPic;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
