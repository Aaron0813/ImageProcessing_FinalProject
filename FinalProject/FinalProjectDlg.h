
// FinalProjectDlg.h : 头文件
//

#pragma once
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CvvImage.h"
#include <ctype.h>  
#include <stdio.h>
#include <opencv2/video/video.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\objdetect\objdetect.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  
#include <iostream>  

/*
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#include <iostream>
*/
using namespace std;
using namespace cv;


// CFinalProjectDlg 对话框
class CFinalProjectDlg : public CDialogEx
{
// 构造
public:
	CFinalProjectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FINALPROJECT_DIALOG };
	 bool bInLoop = true;
	 IplImage* laplace = 0;
	 IplImage* colorlaplace = 0;
	   
	 CvCapture* capture = 0;
	 string cascadeName = "haarcascade_frontalface_alt.xml";
	 string nestedCascadeName = "haarcascade_eye_tree_eyeglasses.xml";

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

	
	//边缘检测
	 void LaplaceConvertion(IplImage* frame, IplImage* laplace);
	//绘制图片
	void DrawPicToHDC(IplImage *img, UINT ID);

	//人脸识别
	 IplImage* FaceRecognization(Mat image);
	 IplImage* DetectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale, bool tryflip);
	
	//foreground extract
	 IplImage* ForegroundExtract(Mat image, BackgroundSubtractorMOG &mog);

	 //friend LPTHREAD_START_ROUTINE startlop(void*);
	 afx_msg void OnBnClickedOk();
};
