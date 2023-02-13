// MFCApplication1View.h: CMFCApplication1View 类的接口
//
#define _CRT_SECURE_NO_WARNINGS
#pragma once
//#include<iostream>
//#include<fstream>
#include<vector>
#include "pch.h"
#include "framework.h"
#include<stdio.h>
#include<iostream>
#include<fstream>




using namespace std;



class CMFCApplication1View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1View)

// 特性
public:
	CMFCApplication1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	

	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawRec();
	afx_msg void OnDrawLine();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMovePic();
	afx_msg void OnSave();
	afx_msg void OnRead();
	afx_msg void OnDraw_Polygon();
};

#ifndef _DEBUG  // MFCApplication1View.cpp 中的调试版本
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

class Shape {
public:
	CDC* pDC;
	FILE* fpp;
	CPoint point1;
	CPoint point2;
	CPoint point3;//点击判断的点
	CPoint point4;//移动后的点
	CPoint pointnum[15];
	int flag =-1;
	int polygoni = -1;
	virtual void draw()
	{
		
	}
	virtual bool judge(CPoint point) {
		return true;
	}
	virtual void Move() {

	}
	virtual void Save() {

	}

	Shape() {
		int c = 1;
	}
};

class My_Circle :public  Shape {
public:
	
	virtual void draw() {
		double r1 = (sqrt)((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush* pOldBrush = pDC->SelectObject(pBrush);
		pDC->SetROP2(R2_BLACK);
		pDC->Ellipse(point1.x - r1, point1.y - r1, point1.x + r1, point1.y + r1);
	}
	virtual bool judge(CPoint point) {
		double r1 = (sqrt)((point1.x - point.x) * (point1.x - point.x) + (point1.y - point.y) * (point1.y - point.y));
		double r2 = (sqrt)((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
		if (abs(r1 - r2) <= 16) {
			return true;
		}
		else return false;
	}
	virtual void Move() {
		double r1 = (sqrt)((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush* pOldBrush = pDC->SelectObject(pBrush);
		pDC->SetROP2(R2_NOT);
		pDC->Ellipse(point1.x - r1, point1.y - r1, point1.x + r1, point1.y + r1);
		point1.x += point4.x - point3.x;
		point1.y += point4.y - point3.y;
		point2.x += point4.x - point3.x;
		point2.y += point4.y - point3.y;
		pDC->SetROP2(R2_BLACK);
		pDC->Ellipse(point1.x - r1, point1.y - r1, point1.x + r1, point1.y + r1);

	}
	virtual void Save() {
		fprintf(fpp, "c\n");
		fprintf(fpp, "%d %d %d %d\n", point1.x, point1.y, point2.x, point2.y);
		
		
	}
};

class My_Line :public Shape {
public:
	
	virtual void draw() {
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush* pOldBrush = pDC->SelectObject(pBrush);
		
		pDC->MoveTo(point1);
		pDC->SetROP2(R2_BLACK);
		pDC->LineTo(point2);
	}
	virtual bool judge(CPoint point) {
		double r1 = (sqrt)((point1.x - point.x) * (point1.x - point.x) + (point1.y - point.y) * (point1.y - point.y));
		if (r1 <= 4) {
			return true;
		}
		else return false;
	}
	virtual void Move() {
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush* pOldBrush = pDC->SelectObject(pBrush);

		pDC->MoveTo(point1);
		pDC->SetROP2(R2_WHITE);
		pDC->LineTo(point2);
		point1.x += point4.x - point3.x;
		point1.y += point4.y - point3.y;
		point2.x += point4.x - point3.x;
		point2.y += point4.y - point3.y;
		pDC->MoveTo(point1);
		pDC->SetROP2(R2_BLACK);
		pDC->LineTo(point2);
	}
	virtual void Save() {
		fprintf(fpp, "l\n");
		fprintf(fpp, "%d %d %d %d\n", point1.x, point1.y, point2.x, point2.y);
		
		
	}
};

class My_Rectangle :public Shape {
public:

	virtual void draw()
	{
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush* pOldBrush = pDC->SelectObject(pBrush);
		pDC->SetROP2(R2_BLACK);
		pDC->Rectangle(point1.x, point1.y, point2.x, point2.y);
	}
	virtual bool judge(CPoint point) {
		double r1 = (sqrt)((point1.x - point.x) * (point1.x - point.x) + (point1.y - point.y) * (point1.y - point.y));
		if (r1 <= 4) {
			return true;
		}
		else return false;
	}
	virtual void Move() {
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush* pOldBrush = pDC->SelectObject(pBrush);
		pDC->SetROP2(R2_NOT);
		pDC->Rectangle(point1.x, point1.y, point2.x, point2.y);
		point1.x += point4.x - point3.x;
		point1.y += point4.y - point3.y;
		point2.x += point4.x - point3.x;
		point2.y += point4.y - point3.y;
		pDC->SetROP2(R2_BLACK);
		pDC->Rectangle(point1.x, point1.y, point2.x, point2.y);
	}
	virtual void Save() {
		fprintf(fpp, "r\n");
		fprintf(fpp, "%d %d %d %d\n", point1.x, point1.y, point2.x, point2.y);
	}
};

//now=1是绘图模式,now==2是移动模式
class My_Polygon :public Shape {
public:
	virtual void draw() {
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush* pOldBrush = pDC->SelectObject(pBrush);
		pDC->MoveTo(pointnum[0]); pDC->SetROP2(R2_BLACK);
		for (int i = 1; i <= flag-1; i++)
		{
			
			pDC->LineTo(pointnum[i ]);
			pDC->MoveTo(pointnum[i]);
		}
		pDC->MoveTo(pointnum[flag-1]);
		
		pDC->LineTo(pointnum[0]);
	}
	virtual bool judge(CPoint point) {
		for (int i = 0; i <= flag - 1; i++) {
			double r = sqrt((point.x - pointnum[i].x) * (point.x - pointnum[i].x) + (point.y - pointnum[i].y) * (point.y - pointnum[i].y));
			if (r <= 7) {
				return true;
			}
		}
		return false;
	}
	virtual void Move() {
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush* pOldBrush = pDC->SelectObject(pBrush);
		pDC->MoveTo(this->pointnum[0]); pDC->SetROP2(R2_NOT);
		for (int i = 1; i <= flag - 1; i++)
		{

			pDC->LineTo(pointnum[i]);
			pDC->MoveTo(pointnum[i]);
		}
		pDC->MoveTo(pointnum[flag - 1]);
		pDC->LineTo(pointnum[0]);

		for (int i = 0; i <= flag - 1; i++) {
			pointnum[i].x += point4.x - point3.x;
			pointnum[i].y += point4.y - point3.y;
		}
		this->draw();

	}
	virtual void Save() {
		fprintf(fpp, "p\n");
		fprintf(fpp, "%d\n",flag);
		for (int i = 0; i <= flag - 1; i++) {
			fprintf(fpp, "%d %d\n", pointnum[i].x, pointnum[i].y);
		}
	}
};