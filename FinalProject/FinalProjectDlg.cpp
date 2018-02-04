
// FinalProjectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FinalProjectDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
IplImage* planes[3] = { 0, 0, 0 };  // ���ͼ����
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


// CFinalProjectDlg �Ի���

CFinalProjectDlg::CFinalProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFinalProjectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CFinalProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFinalProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFinalProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CFinalProjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFinalProjectDlg ��Ϣ�������

BOOL CFinalProjectDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFinalProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFinalProjectDlg::OnPaint()
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
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFinalProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//Open Button�Ĵ���
void CFinalProjectDlg::OnBnClickedButton1()
{
	//��Ϣ�������
	static MSG msg;

	/*     if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
	capture = cvCaptureFromCAM( argc == 2 ? argv[1][0] - '0' : 0 );
	else if( argc == 2 )
	capture = cvCaptureFromAVI( argv[1] ); */
	//capture = cvCaptureFromAVI( "3.avi" );  

	capture = cvCaptureFromCAM(0);

	if (!capture)
	{
		fprintf(stderr, "Could not initialize capturing.../n");
		return;
	}

	IplImage* faceRecognize = 0;
	IplImage* forgroundExtract = 0;
	BackgroundSubtractorMOG mog;

	while (bInLoop)
	{
		//��ֹUI����  ��Ӧǰ��
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		IplImage* frame = 0;
		Mat image;
		Mat image02;
		 
		//������ͷ�����ļ���ץȡ������һ֡  
		//������ֵΪNULL��˵��������Ƶ�����һ֡��  
		frame = cvQueryFrame(capture);
		if (!frame)
			break;
		image = (cv::Mat(frame, true)).clone();
		image02 = image.clone();

		LaplaceConvertion(frame, laplace);
		faceRecognize = FaceRecognization(image);
		forgroundExtract = ForegroundExtract(image02, mog);
		DrawPicToHDC(frame, IDC_STATIC_01);
		DrawPicToHDC(colorlaplace, IDC_STATIC_02);
		DrawPicToHDC(faceRecognize, IDC_STATIC_03);
		DrawPicToHDC(forgroundExtract, IDC_STATIC_04);

	} 


	cvReleaseCapture(&capture);
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startlop, NULL, 0, 0);
	/*
	while (bInLoop)
	{
		IplImage* frame = 0;
		Mat image;
		Mat image02;
		//cvQueryFrame  
		//  
		//������ͷ�����ļ���ץȡ������һ֡  
		//IplImage* cvQueryFrame( CvCapture* capture );  
		//capture   
		//��Ƶ��ȡ�ṹ��  
		//����cvQueryFrame������ͷ�����ļ���ץȡһ֡��Ȼ���ѹ��������һ֡��  
		//������������Ǻ���cvGrabFrame�ͺ���cvRetrieveFrame��һ����õ���ϡ�  
		//���ص�ͼ�񲻿��Ա��û��ͷŻ����޸ġ� ץȡ��capture��ָ����һ֡��  
		//����cvSetCaptureProperty����capture�����ʵ�֡��  
		//  
		//ע�⣺ cvQueryFrame���ص�ָ������ָ��ͬһ���ڴ档����cvQueryFrame�󿽱�һ��  
		//�����ҷ��ص�֡��ҪFLIP��ŷ���OPENCV������ϵ�� ������ֵΪNULL��˵��������Ƶ�����һ֡��  
		frame = cvQueryFrame(capture);
		if (!frame)
			break;
		image = (cv::Mat(frame,true)).clone();
		image02 = image.clone();
		
		LaplaceConvertion(frame, laplace);
		faceRecognize = FaceRecognization(image);
		forgroundExtract = ForegroundExtract(image02, mog);
		DrawPicToHDC(frame, IDC_STATIC_01);
		DrawPicToHDC(colorlaplace, IDC_STATIC_02);
		DrawPicToHDC(faceRecognize, IDC_STATIC_03);
		DrawPicToHDC(forgroundExtract, IDC_STATIC_04);
				
	}*/
	
	
}

void CFinalProjectDlg::DrawPicToHDC(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img); // ����ͼƬ
	cimg.DrawToHDC(hDC, &rect); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC(pDC);
}

void CFinalProjectDlg::LaplaceConvertion(IplImage* frame, IplImage* laplace)
{
	int i;
	if (!laplace)
	{
		for (i = 0; i < 3; i++)
			planes[i] = cvCreateImage(cvSize(frame->width, frame->height), 8, 1);
		laplace = cvCreateImage(cvSize(frame->width, frame->height),
			IPL_DEPTH_16S, 1);
		colorlaplace = cvCreateImage(cvSize(frame->width, frame->height), 8, 3);
	}
	cvCvtPixToPlane(frame, planes[0], planes[1], planes[2], 0);
	for (i = 0; i < 3; i++)
	{
		
		//����ͼ��� Laplacian �任  
		//�˴�С (�� cvSobel �ж���һ��).  
		cvLaplace(planes[i], laplace, 3); // 3: aperture_size  
	
		//ʹ�����Ա任ת����������Ԫ�س�8λ�޷�������  
		//ԭ����Ԫ�ذ��������ź���ӵ�ֵ��  
		//���� cvConvertScaleAbs ��ǰһ��������ͬ�ģ������Ǵ����任����ľ���ֵ��  
		//dst(I)=abs(src(I)*scale + (shift,shift,...))  
		//����ֻ֧��Ŀ������������Ϊ 8u (8-bit �޷���) , ���ڱ�����ͺ�����Ч��cvConvertScale �� cvAbs ����������  
		cvConvertScaleAbs(laplace, planes[i], 1, 0);  // planes[] = ABS(laplace)  
	}
	//cvCvtPixToPlane��cvCvtPlaneToPix���溯��  
	cvCvtPlaneToPix(planes[0], planes[1], planes[2], 0, colorlaplace);
	colorlaplace->origin = frame->origin;   //�����ǽṹһ��  
}


IplImage* CFinalProjectDlg::FaceRecognization(Mat image)
{
	//Mat image;//��Ƶ����ͼ�����ͼƬ  
	bool tryflip = false;//���Ȳ����Է�ת  
	CascadeClassifier cascade, nestedCascade;//������  
	double scale = 4;//��ģ=1  
	IplImage* result=0;
	if (!cascade.load(cascadeName))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return NULL;
	}
	
	// ѭ����׽��ֱ���û���������ѭ����    
	if (!image.empty())
	{
		result = DetectAndDraw(image, cascade, nestedCascade, scale, tryflip);
		cout << "123123" << endl;
	}

	return result;
}
IplImage* CFinalProjectDlg::DetectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale, bool tryflip)
{
	//IplImage *iplimg = 0;
	int i = 0;
	double t = 0;
	vector<Rect> faces, faces2;//��תǰ����face����ת�����face2  
	const static Scalar colors[] = { CV_RGB(0, 0, 255), CV_RGB(0, 128, 255), CV_RGB(0, 255, 255), CV_RGB(0, 255, 0),
		CV_RGB(255, 128, 0), CV_RGB(255, 255, 0), CV_RGB(255, 0, 0), CV_RGB(255, 0, 255) };//���ڱ�ʶ������ȦȦ����ɫ  
	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);//cvRound��һ��double�͵��������������룬������һ��������  
	cvtColor(img, gray, COLOR_BGR2GRAY);//��ɻҶ�  
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);//˫���Բ�ֵ��Ĭ�Ϸ�����  
	equalizeHist(smallImg, smallImg);//ʹ�Ҷ�ͼ��ֱ��ͼ���⻯,��ǿͼ������ȼ��Աȶ�  

	t = (double)cvGetTickCount();//�õ����ڵ�ʱ��  
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CASCADE_FIND_BIGGEST_OBJECT  
		//|CASCADE_DO_ROUGH_SEARCH  
		| CASCADE_SCALE_IMAGE
		,
		Size(30, 30));
	if (tryflip)
	{
		flip(smallImg, smallImg, 1);
		cascade.detectMultiScale(smallImg, faces2,
			1.1, 2, 0
			//|CASCADE_FIND_BIGGEST_OBJECT  
			//|CASCADE_DO_ROUGH_SEARCH  
			| CASCADE_SCALE_IMAGE
			,
			Size(30, 30));
		for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++)
		{
			faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
		}
	}
	t = (double)cvGetTickCount() - t;//�ó�ʶ�����õ�ʱ��  
	printf("detection time = %g ms\nthe number of faces = %d\n", t / ((double)cvGetTickFrequency()*1000.), faces.size());
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)//��ȦȦ  
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i % 8];
		int radius;

		double aspect_ratio = (double)r->width / r->height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
			cvPoint(cvRound((r->x + r->width - 1)*scale), cvRound((r->y + r->height - 1)*scale)),
			color, 3, 8, 0);
		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(*r);
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CASCADE_FIND_BIGGEST_OBJECT  
			//|CASCADE_DO_ROUGH_SEARCH  
			//|CASCADE_DO_CANNY_PRUNING  
			| CASCADE_SCALE_IMAGE
			,
			Size(30, 30));
		for (vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++)
		{
			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
	}

	//���
	IplImage imgTmp = img;
	IplImage *input = cvCloneImage(&imgTmp);
	return input;
}

IplImage* CFinalProjectDlg::ForegroundExtract(Mat image, BackgroundSubtractorMOG &mog)
{
	Mat foreground;	// ǰ��ͼƬ
	// ��ϸ�˹����
	
	
		// ���±���ͼƬ�������ǰ��
		mog(image, foreground, 0.01);
		// �����ǰ��ͼƬ������2ֵͼƬ��Ҫ����һ����ʾ 
		threshold(foreground, foreground, 128, 255, THRESH_BINARY_INV);
		// show foreground
		//imshow("Extracted Foreground", foreground);

	IplImage imgTmp = foreground;
	IplImage *input = cvCloneImage(&imgTmp);
	return input;
}

void CFinalProjectDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	bInLoop = false;
	CDialogEx::OnOK();
}
