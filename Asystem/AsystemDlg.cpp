
// AsystemDlg.cpp: 实现文件
//
#include "pch.h"
#include "framework.h"
#include "Asystem.h"
#include "AsystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAsystemDlg 对话框



CAsystemDlg::CAsystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASYSTEM_DIALOG, pParent)
	, m_Name(_T(""))
	, m_Number(_T(""))
	, m_Sex(_T(""))
	, m_Phone(_T(""))
	, m_Mailbox(_T(""))
	, m_Home(_T(""))
	, m_Show(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Eclass, m_Class);
	DDX_Text(pDX, IDC_Ename, m_Name);
	DDX_Text(pDX, IDC_Enumber, m_Number);
	DDX_Text(pDX, IDC_Esex, m_Sex);
	DDX_Text(pDX, IDC_Ephone, m_Phone);
	DDX_Text(pDX, IDC_Emailbox, m_Mailbox);
	DDX_Text(pDX, IDC_Ehome, m_Home);
	DDX_Text(pDX, IDC_Eshow, m_Show);
	DDX_Control(pDX, IDC_LAll, m_List);
}

BEGIN_MESSAGE_MAP(CAsystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Add_B, &CAsystemDlg::OnBnClickedAddB)
	ON_BN_CLICKED(IDC_Search_B, &CAsystemDlg::OnBnClickedSearchB)
	ON_BN_CLICKED(IDC_Modify_B, &CAsystemDlg::OnBnClickedModifyB)
	ON_BN_CLICKED(IDC_Delete_B, &CAsystemDlg::OnBnClickedDeleteB)
	ON_BN_CLICKED(IDC_Bclearall, &CAsystemDlg::OnBnClickedBclearall)
	ON_BN_CLICKED(IDC_Bclearin, &CAsystemDlg::OnBnClickedBclearin)
	ON_BN_CLICKED(IDCANCEL, &CAsystemDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAsystemDlg 消息处理程序
//设置结构体数组用于保存数据
struct Msg {
	CString Class;
	CString Name;
	CString Number;
	CString Sex;
	CString Phone;
	CString Mailbox;
	CString Home;
	Msg*next;
}*msg = new Msg;

void change(int*i) {
	if (*i == 7)*i = 1;
	else if (*i < 7)*i = *i + 1;
}

CString All;//用于保存个人信息的字符串
Msg*index;//设置递增指针用于添加

BOOL CAsystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	int i = 1;
	msg->next = NULL;
	fstream File;
	string str;//用于保存获取的行
	stringstream ss;//把保存的行给予字符串流
	string item;//把字符串流分割出的字符串给予item
	CString citem;
	File.open("message.csv",ios::in);
	getline(File, str);//先读文件一次把列名加入
	citem = str.c_str();
	m_List.AddString(citem);
	if (getline(File, str)) {//原系统中已经保存了一些通讯录信息
		do {
			index = msg;
			while (index->next != NULL) { index = index->next; }
			Msg*node = new Msg;
			node->next = NULL;
			index->next = node;
			index = index->next;
			ss.clear();//重置字符串流
			ss << str;
			while (getline(ss, item, ','))//每一个新的ss信息放入一个新节点中
			{
				citem = item.c_str();
				switch (i) {
				case 1:
					index->Class = citem; break;
				case 2:
					index->Name = citem; break;
				case 3:
					index->Number = citem; break;
				case 4:
					index->Sex = citem; break;
				case 5:
					index->Phone = citem; break;
				case 6:
					index->Mailbox = citem; break;
				case 7:
					index->Home = citem; break;
				}
				change(&i);
			}
			All = index->Class + "," + index->Name + "," + index->Number + "," + index->Sex + "," + index->Phone + "," + index->Mailbox + "," + index->Home;
			m_List.AddString(All);
		} while (getline(File, str));
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAsystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAsystemDlg::OnPaint()
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
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAsystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAsystemDlg::OnBnClickedAddB()//添加功能
{	// TODO: 在此添加控件通知处理程序代码
	//重置index
	index = msg;
	while (index->next != NULL) { index = index->next; }
	UpdateData(TRUE);//传入数据
	Msg*search = msg->next;
	if (m_Name != ""&&m_Number != "") {//必须输入学号与姓名
		if (search != NULL) {
			while (search != NULL &&m_Number!=search->Number&&search->next != NULL) { search = search->next; }
			if (m_Number == search->Number)return;//出现重复学号不予处理
		}
		Msg*node = new Msg;//利用链表存储信息
		node->next = NULL;
		index->next = node;
		index = index->next;
		index->Class = m_Class;
		index->Name = m_Name;
		index->Number = m_Number;
		index->Sex = m_Sex;
		index->Phone = m_Phone;
		index->Mailbox = m_Mailbox;
		index->Home = m_Home;
		All = m_Class + "," + m_Name + ","  + m_Number + "," + m_Sex + "," + m_Phone + "," + m_Mailbox + "," + m_Home;
		m_List.AddString(All);//在listbox控件中添加新信息
		UpdateData(FALSE);//显示数据
		MessageBox(_T("添加成功"));
	}
	
}


void CAsystemDlg::OnBnClickedSearchB()//查找功能
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Msg*search = msg->next;
	if (m_Number!=L""&&search!=NULL)
	{
		while (search!=NULL&&m_Number != search->Number&&search->next != NULL){search = search->next;}
		if ((m_Name == search->Name||m_Name=="")&&m_Number==search->Number) {//查找时必须输入学号，姓名可不输入，若输入姓名需要输入正确的姓名，否则查找不成功
			All = search->Class + "," + search->Name + ","  + search->Number + "," + search->Sex + "," + search->Phone + "," + search->Mailbox + "," + search->Home;
			m_List.FindString(-1, All);
			m_Class = search->Class;
			m_Name = search->Name;
			m_Number = search->Number;
			m_Sex = search->Sex;
			m_Phone = search->Phone;
			m_Mailbox = search->Mailbox;
			m_Home = search->Home;
		}
	}
	MessageBox(L"查找成功");
	UpdateData(FALSE);
}


void CAsystemDlg::OnBnClickedModifyB()//修改功能
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Msg*search = msg->next;
	if (search != NULL&&m_Number!=""&&m_Name!="")//修改必须输入学号姓名
	{
		while (m_Number!=search->Number&&search->next != NULL) { search = search->next; }
		if ( m_Number == search->Number) {
			All = search->Class + "," + search->Name + "," + search->Number + "," + search->Sex + "," + search->Phone + "," + search->Mailbox + "," + search->Home;
			int column=m_List.FindString(-1, All);
			search->Class = m_Class;
			search->Name = m_Name;
			search->Number=m_Number;
			search->Sex=m_Sex;
			search->Phone=m_Phone;
			search->Mailbox=m_Mailbox;
			search->Home=m_Home;
			m_List.DeleteString(column);
			All = search->Class + "," + search->Name + "," + search->Number + "," + search->Sex + "," + search->Phone + "," + search->Mailbox + "," + search->Home;
			m_List.AddString(All);
			MessageBox(L"修改成功");
		}
	}
}


void CAsystemDlg::OnBnClickedDeleteB()//删除功能
{
	// TODO: 在此添加控件通知处理程序代码
	Msg*search = msg->next;//指向要删除的记录的当前节点
	Msg*pri = msg;//前指针指向要删除的记录的前一个节点
	CString res;//获取目标行的数据
	UpdateData(TRUE);
	int list_sel = m_List.GetSelCount();
	if (list_sel > 0&&search!=NULL) {
		int *p = new int[list_sel];
		m_List.GetSelItems(list_sel, p);//获取要删除的行号
		for (int i = list_sel - 1; i >= 0; i--) {
			//由于可多行删除，故每次循环需要重置pri和search指针的位置
			pri = msg;
			search = msg->next;
			m_List.GetText(p[i], res);
			All = search->Class + "," + search->Name + "," + search->Number + "," + search->Sex + "," + search->Phone + "," + search->Mailbox + "," + search->Home;//初始化All
			while (All!=res&& search->next != NULL) {
				pri = pri->next;
				search = search->next;
				All = search->Class + "," + search->Name + "," + search->Number + "," + search->Sex + "," + search->Phone + "," + search->Mailbox + "," + search->Home;
			}
			if (All == res)//找到要删除的节点
			{
				pri->next = search->next;
				delete search;
			}
			m_List.DeleteString(p[i]);
		}
	}
	else if(search != NULL&&m_Number!="") {
		while (m_Number != search->Number&&search->next != NULL) 
		{
			search = search->next;
			pri = pri->next;
		}
		if (m_Number == search->Number)//找到要删除的节点
		{
			All = search->Class + "," + search->Name + "," + search->Number + "," + search->Sex + "," + search->Phone + "," + search->Mailbox + "," + search->Home;
			int column=m_List.FindString(-1, All);
			pri->next = search->next;
			delete search;
			m_List.DeleteString(column);
		}
	}
}


void CAsystemDlg::OnBnClickedBclearall()
{
	// TODO: 在此添加控件通知处理程序代码
	m_List.ResetContent();
	Msg*search = msg->next;
	Msg*p;
	msg->next = NULL;
	while (search != NULL ) {
		p = search;
		search = search->next;
		delete p;
	}
}


void CAsystemDlg::OnBnClickedBclearin()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Class = L"";
	m_Name = L"";
	m_Number = L"";
	m_Sex = L"";
	m_Phone = L"";
	m_Mailbox = L"";
	m_Home = "";
	UpdateData(FALSE);
}


void CAsystemDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	fstream File;
	Msg*search = msg->next;
	string column ( "Class,Name,ID,Sex,Phone,Mailbox,Home");
	string row;
	File.open("message.csv", ios::out);
	File << column << "\n";
	while (search != NULL) {
		All = search->Class + "," + search->Name + "," + search->Number + "," + search->Sex + "," + search->Phone + "," + search->Mailbox + "," + search->Home;
		row = CT2A(All.GetString());
		File << row << "\n";
		search = search->next;
	}
	File.close();
	MessageBox(L"通讯录操作已保存");
	CDialogEx::OnCancel();
}
