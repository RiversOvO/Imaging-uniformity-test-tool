#pragma execution_character_set("utf-8")//解决中文乱码
#include "mainwindow.h"
#include <QPushButton>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
                 /*************************************************************************构造函数（布局区域）****************************************************************************************/
                 MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)//创建一个主窗口
{
    QString configFile = QCoreApplication::applicationDirPath() + "/G1Pro_Test_Tool_1_V1.0.0配置文件.ini";
    QSettings settings(configFile, QSettings::IniFormat);

    // 初始化上限值
    m_centerBrightnessLimit = settings.value("limits/centerBrightnessLimit").toDouble();
    m_joint1BrightnessLimit = settings.value("limits/joint1BrightnessLimit").toDouble();
    m_joint2BrightnessLimit = settings.value("limits/joint2BrightnessLimit").toDouble();
    m_centerRGLimit = settings.value("limits/centerRGLimit").toDouble();
    m_joint1RGLimit = settings.value("limits/joint1RGLimit").toDouble();
    m_joint2RGLimit = settings.value("limits/joint2RGLimit").toDouble();
    m_centerBGLimit = settings.value("limits/centerBGLimit").toDouble();
    m_joint1BGLimit = settings.value("limits/joint1BGLimit").toDouble();
    m_joint2BGLimit = settings.value("limits/joint2BGLimit").toDouble();

    // 初始化检测区域
    m_X1 = settings.value("regions/X1").toDouble();
    m_Y1 = settings.value("regions/Y1").toDouble();
    m_W1 = settings.value("regions/W1").toDouble();
    m_H1 = settings.value("regions/H1").toDouble();
    m_X2 = settings.value("regions/X2").toDouble();
    m_Y2 = settings.value("regions/Y2").toDouble();
    m_W2 = settings.value("regions/W2").toDouble();
    m_H2 = settings.value("regions/H2").toDouble();
    m_X3 = settings.value("regions/X3").toDouble();
    m_Y3 = settings.value("regions/Y3").toDouble();
    m_W3 = settings.value("regions/W3").toDouble();
    m_H3 = settings.value("regions/H3").toDouble();
    m_X4 = settings.value("regions/X4").toDouble();
    m_Y4 = settings.value("regions/Y4").toDouble();
    m_W4 = settings.value("regions/W4").toDouble();
    m_H4 = settings.value("regions/H4").toDouble();
    m_X5 = settings.value("regions/X5").toDouble();
    m_Y5 = settings.value("regions/Y5").toDouble();
    m_W5 = settings.value("regions/W5").toDouble();
    m_H5 = settings.value("regions/H5").toDouble();
    m_X6 = settings.value("regions/X6").toDouble();
    m_Y6 = settings.value("regions/Y6").toDouble();
    m_W6 = settings.value("regions/W6").toDouble();
    m_H6 = settings.value("regions/H6").toDouble();

    // 获取电脑屏幕的大小
    QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
    int width = screenRect.width();
    int height = screenRect.height();

    // 设置窗口大小和标题
    setGeometry(0, 0, width - 200, height - 200);
    setWindowTitle(tr("图像亮度与色彩对比分析"));

    // 创建中心控件
    QWidget* centralWidget = new QWidget(this);//创建一个QWidget对象,并将其设置为当前窗口的子对象,此QWidget将用作主要的工作区域

    // 创建水平布局
    QHBoxLayout* hLayout = new QHBoxLayout();//用于将QWidget的子控件水平排列

    // 创建左边垂直布局
    QVBoxLayout* vLayoutL = new QVBoxLayout();//用于将QWidget的子控件垂直排列

    // 判断结果显示区域
    m_centerResultLabel = new QLabel("暂无中心区域判断");
    m_centerResultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centerResultLabel->setAlignment(Qt::AlignCenter);
    vLayoutL->addWidget(m_centerResultLabel);
    m_joint1ResultLabel = new QLabel("暂无左拼接缝判断");
    m_joint1ResultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint1ResultLabel->setAlignment(Qt::AlignCenter);
    vLayoutL->addWidget(m_joint1ResultLabel);
    m_joint2ResultLabel = new QLabel("暂无右拼接缝判断");
    m_joint2ResultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint2ResultLabel->setAlignment(Qt::AlignCenter);
    vLayoutL->addWidget(m_joint2ResultLabel);
    vLayoutL->addStretch();

    // 创建左边水平布局
    QHBoxLayout* hLayoutL1 = new QHBoxLayout();
    QHBoxLayout* hLayoutL2 = new QHBoxLayout();
    QHBoxLayout* hLayoutL3 = new QHBoxLayout();

    // 打开中心图片的按钮
    QPushButton* openCenterButton = new QPushButton(tr("中心图片"));//创建了一个QPushButton对象
    QObject::connect(openCenterButton, &QPushButton::clicked, this, [this](){
        openCenterImage();
        markCenterImageRegions();
    });
    hLayoutL1->addWidget(openCenterButton);//将QPushButton对象添加到水平布局管理器中

    // 输出计算结果的按钮
    QPushButton* resultButton = new QPushButton(tr("计算结果"));//创建了一个QPushButton对象
    QObject::connect(resultButton, &QPushButton::clicked, this, [this](){
        CenterCalculate();
        Joint1Calculate();
        Joint2Calculate();
    });
    hLayoutL1->addWidget(resultButton);//将QPushButton对象添加到水平布局管理器中

    vLayoutL->addLayout(hLayoutL1);// 将左边水平布局1添加到左边垂直布局中

    // 打开左边缘图片的按钮
    QPushButton* openLeftButton = new QPushButton(tr("左边缘图片"));//创建了一个QPushButton对象
    QObject::connect(openLeftButton, &QPushButton::clicked, this, [this](){
        openJoint1Image();
        markJoint1ImageRegions();
    });
    hLayoutL2->addWidget(openLeftButton);//将QPushButton对象添加到水平布局管理器中

    // 保存结果的按钮
    QPushButton* saveButton = new QPushButton(tr("&保存结果"));//创建了一个QPushButton对象
    QObject::connect(saveButton, &QPushButton::clicked, this, [this](){
        saveResultTextToFile();
        saveMarkedImageToFile();
    });
    hLayoutL2->addWidget(saveButton);//将QPushButton对象添加到水平布局管理器中

    vLayoutL->addLayout(hLayoutL2);// 将左边水平布局2添加到左边垂直布局中

    // 打开右边缘图片的按钮
    QPushButton* openRightButton = new QPushButton(tr("右边缘图片"));//创建了一个QPushButton对象
    QObject::connect(openRightButton, &QPushButton::clicked, this, [this](){
        openJoint2Image();
        markJoint2ImageRegions();
    });
    hLayoutL3->addWidget(openRightButton);//将QPushButton对象添加到水平布局管理器中

    // 设置阈值的按钮
    QPushButton* thresholdButton = new QPushButton(tr("&阈值设置"));//创建了一个QPushButton对象
    connect(thresholdButton, &QPushButton::clicked, this, &MainWindow::setThreshold);//将按钮的clicked信号连接到主窗口的setThreshold()槽函数
    hLayoutL3->addWidget(thresholdButton);//将QPushButton对象添加到水平布局管理器中

    vLayoutL->addLayout(hLayoutL3);// 将左边水平布局3添加到左边垂直布局中

    // 创建右边垂直布局
    QVBoxLayout* vLayoutR = new QVBoxLayout();

    // 创建右边水平布局
    QHBoxLayout* hLayoutR1 = new QHBoxLayout();
    QHBoxLayout* hLayoutR2 = new QHBoxLayout();
    QHBoxLayout* hLayoutR3 = new QHBoxLayout();
    QHBoxLayout* hLayoutR4 = new QHBoxLayout();
    QHBoxLayout* hLayoutR5 = new QHBoxLayout();
    QHBoxLayout* hLayoutR6 = new QHBoxLayout();

    // 显示中心区域图像的标签1
    m_centerLabel1 = new QLabel(tr("中心区域显示区"));
    m_centerLabel1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centerLabel1->setAlignment(Qt::AlignCenter);
    hLayoutR1->addWidget(m_centerLabel1);// 将 QLabel添加到水平布局中

    // 显示中心区域图像的标签2
    m_centerLabel2 = new QLabel(tr("中心区域显示区"));
    m_centerLabel2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centerLabel2->setAlignment(Qt::AlignCenter);
    hLayoutR1->addWidget(m_centerLabel2);// 将 QLabel添加到水平布局中

    vLayoutR->addLayout(hLayoutR1,3);// 将右边水平布局1添加到右边垂直布局中

    // 显示拼接区域1图像的标签1
    m_joint1Label1 = new QLabel(tr("左拼接缝显示区"));
    m_joint1Label1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint1Label1->setAlignment(Qt::AlignCenter);
    hLayoutR2->addWidget(m_joint1Label1);// 将 QLabel添加到水平布局中

    // 显示拼接区域1图像的标签2
    m_joint1Label2 = new QLabel(tr("左拼接缝显示区"));
    m_joint1Label2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint1Label2->setAlignment(Qt::AlignCenter);
    hLayoutR2->addWidget(m_joint1Label2);// 将 QLabel添加到水平布局中

    vLayoutR->addLayout(hLayoutR2,3);// 将右边水平布局2添加到右边垂直布局中

    // 显示拼接区域2图像的标签1
    m_joint2Label1 = new QLabel(tr("右拼接缝显示区"));
    m_joint2Label1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint2Label1->setAlignment(Qt::AlignCenter);
    hLayoutR3->addWidget(m_joint2Label1);// 将 QLabel添加到水平布局中

    // 显示拼接区域2图像的标签2
    m_joint2Label2 = new QLabel(tr("右拼接缝显示区"));
    m_joint2Label2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint2Label2->setAlignment(Qt::AlignCenter);
    hLayoutR3->addWidget(m_joint2Label2);// 将 QLabel添加到水平布局中

    vLayoutR->addLayout(hLayoutR3,3);// 将右边水平布局3添加到右边垂直布局中

    // 中心区域亮度测试数据结果显示区域
    m_centerBrightnessResultLabel = new QLabel(tr("中心区域亮度测试数据结果显示区"));
    m_centerBrightnessResultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centerBrightnessResultLabel->setAlignment(Qt::AlignCenter);
    hLayoutR4->addWidget(m_centerBrightnessResultLabel);// 将 QLabel添加到水平布局中

    // 中心区域色彩测试数据结果显示区域
    m_centerColorResultLabel = new QLabel(tr("中心区域色彩测试数据结果显示区"));
    m_centerColorResultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centerColorResultLabel->setAlignment(Qt::AlignCenter);
    hLayoutR4->addWidget(m_centerColorResultLabel);// 将 QLabel添加到水平布局中

    vLayoutR->addLayout(hLayoutR4,1);// 将右边水平布局4添加到右边垂直布局中

    // 拼接区域1亮度测试数据结果显示区域
    m_joint1BrightnessResultLabel = new QLabel(tr("左拼接缝亮度测试数据结果显示区"));
    m_joint1BrightnessResultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint1BrightnessResultLabel->setAlignment(Qt::AlignCenter);
    hLayoutR5->addWidget(m_joint1BrightnessResultLabel);// 将 QLabel添加到水平布局中

    // 拼接区域1色彩测试数据结果显示区域
    m_joint1ColorResultLabel = new QLabel(tr("左拼接缝色彩测试数据结果显示区"));
    m_joint1ColorResultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint1ColorResultLabel->setAlignment(Qt::AlignCenter);
    hLayoutR5->addWidget(m_joint1ColorResultLabel);// 将 QLabel添加到水平布局中

    vLayoutR->addLayout(hLayoutR5,1);// 将右边水平布局5添加到右边垂直布局中

    // 拼接区域2亮度测试数据结果显示区域
    m_joint2BrightnessResultLabel = new QLabel(tr("右拼接缝亮度测试数据结果显示区"));
    m_joint2BrightnessResultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint2BrightnessResultLabel->setAlignment(Qt::AlignCenter);
    hLayoutR6->addWidget(m_joint2BrightnessResultLabel);// 将 QLabel添加到水平布局中

    // 拼接区域2色彩测试数据结果显示区域
    m_joint2ColorResultLabel = new QLabel(tr("右拼接缝色彩测试数据结果显示区"));
    m_joint2ColorResultLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_joint2ColorResultLabel->setAlignment(Qt::AlignCenter);
    hLayoutR6->addWidget(m_joint2ColorResultLabel);// 将 QLabel添加到水平布局中

    vLayoutR->addLayout(hLayoutR6,1);// 将右边水平布局6添加到右边垂直布局中

    hLayout->addLayout(vLayoutL, 1);//将左侧垂直布局管理器vLayoutL添加到水平布局管理器hLayout中，并设置占比为1
    hLayout->addLayout(vLayoutR, 3);//将右侧垂直布局管理器vLayoutR添加到水平布局管理器hLayout中，并设置占比为3
    centralWidget->setLayout(hLayout);//将水平布局管理器hLayout设置为中心窗口centralWidget的布局管理器
    setCentralWidget(centralWidget);
}
/*************************************************************************功能区域****************************************************************************************/
// 析构函数
MainWindow::~MainWindow()
{
}

// 设置阈值函数
void MainWindow::setThreshold()
{
    QDialog dialog(this);
    dialog.setWindowTitle(tr("设置区域参数"));

    QFormLayout formLayout(&dialog);

    QDoubleSpinBox* ASpinBox = new QDoubleSpinBox();
    ASpinBox->setRange(0, 10000);
    ASpinBox->setValue(m_centerBrightnessLimit);
    formLayout.addRow(tr("中心区域亮度绝对差上限:"), ASpinBox);

    QDoubleSpinBox* BSpinBox = new QDoubleSpinBox();
    BSpinBox->setRange(0, 10000);
    BSpinBox->setValue(m_joint1BrightnessLimit);
    formLayout.addRow(tr("左拼接缝区域亮度绝对差上限:"), BSpinBox);

    QDoubleSpinBox* CSpinBox = new QDoubleSpinBox();
    CSpinBox->setRange(0, 10000);
    CSpinBox->setValue(m_joint2BrightnessLimit);
    formLayout.addRow(tr("右拼接缝区域亮度绝对差上限:"), CSpinBox);

    QDoubleSpinBox* DSpinBox = new QDoubleSpinBox();
    DSpinBox->setRange(0, 10000);
    DSpinBox->setValue(m_centerRGLimit);
    formLayout.addRow(tr("中心区域R/G绝对差上限:"), DSpinBox);

    QDoubleSpinBox* ESpinBox = new QDoubleSpinBox();
    ESpinBox->setRange(0, 10000);
    ESpinBox->setValue(m_joint1RGLimit);
    formLayout.addRow(tr("左拼接缝区域R/G绝对差上限:"), ESpinBox);

    QDoubleSpinBox* FSpinBox = new QDoubleSpinBox();
    FSpinBox->setRange(0, 10000);
    FSpinBox->setValue(m_joint2RGLimit);
    formLayout.addRow(tr("右拼接缝区域R/G绝对差上限:"), FSpinBox);

    QDoubleSpinBox* GSpinBox = new QDoubleSpinBox();
    GSpinBox->setRange(0, 10000);
    GSpinBox->setValue(m_centerBGLimit);
    formLayout.addRow(tr("中心区域B/G绝对差上限:"), GSpinBox);

    QDoubleSpinBox* HSpinBox = new QDoubleSpinBox();
    HSpinBox->setRange(0, 10000);
    HSpinBox->setValue(m_joint1BGLimit);
    formLayout.addRow(tr("左拼接缝区域B/G绝对差上限:"), HSpinBox);

    QDoubleSpinBox* ISpinBox = new QDoubleSpinBox();
    ISpinBox->setRange(0, 10000);
    ISpinBox->setValue(m_joint2BGLimit);
    formLayout.addRow(tr("右拼接缝区域B/G绝对差上限:"), ISpinBox);

    QDoubleSpinBox* JSpinBox = new QDoubleSpinBox();
    JSpinBox->setRange(0, 10000);
    JSpinBox->setValue(m_X1);
    formLayout.addRow(tr("中心区域(左)左上角横坐标:"), JSpinBox);

    QDoubleSpinBox* KSpinBox = new QDoubleSpinBox();
    KSpinBox->setRange(0, 10000);
    KSpinBox->setValue(m_Y1);
    formLayout.addRow(tr("中心区域(左)左上角纵坐标:"), KSpinBox);

    QDoubleSpinBox* LSpinBox = new QDoubleSpinBox();
    LSpinBox->setRange(0, 10000);
    LSpinBox->setValue(m_W1);
    formLayout.addRow(tr("中心区域(左)宽度:"), LSpinBox);

    QDoubleSpinBox* MSpinBox = new QDoubleSpinBox();
    MSpinBox->setRange(0, 10000);
    MSpinBox->setValue(m_H1);
    formLayout.addRow(tr("中心区域(左)高度:"), MSpinBox);

    QDoubleSpinBox* NSpinBox = new QDoubleSpinBox();
    NSpinBox->setRange(0, 10000);
    NSpinBox->setValue(m_X2);
    formLayout.addRow(tr("中心区域(右)左上角横坐标:"), NSpinBox);

    QDoubleSpinBox* OSpinBox = new QDoubleSpinBox();
    OSpinBox->setRange(0, 10000);
    OSpinBox->setValue(m_Y2);
    formLayout.addRow(tr("中心区域(右)左上角纵坐标:"), OSpinBox);

    QDoubleSpinBox* PSpinBox = new QDoubleSpinBox();
    PSpinBox->setRange(0, 10000);
    PSpinBox->setValue(m_W2);
    formLayout.addRow(tr("中心区域(右)宽度:"), PSpinBox);

    QDoubleSpinBox* QSpinBox = new QDoubleSpinBox();
    QSpinBox->setRange(0, 10000);
    QSpinBox->setValue(m_H2);
    formLayout.addRow(tr("中心区域(右)高度:"), QSpinBox);

    QDoubleSpinBox* RSpinBox = new QDoubleSpinBox();
    RSpinBox->setRange(0, 10000);
    RSpinBox->setValue(m_X3);
    formLayout.addRow(tr("左拼接缝区域(左)左上角横坐标:"), RSpinBox);

    QDoubleSpinBox* SSpinBox = new QDoubleSpinBox();
    SSpinBox->setRange(0, 10000);
    SSpinBox->setValue(m_Y3);
    formLayout.addRow(tr("左拼接缝区域(左)左上角纵坐标:"), SSpinBox);

    QDoubleSpinBox* TSpinBox = new QDoubleSpinBox();
    TSpinBox->setRange(0, 10000);
    TSpinBox->setValue(m_W3);
    formLayout.addRow(tr("左拼接缝区域(左)宽度:"), TSpinBox);

    QDoubleSpinBox* USpinBox = new QDoubleSpinBox();
    USpinBox->setRange(0, 10000);
    USpinBox->setValue(m_H3);
    formLayout.addRow(tr("左拼接缝区域(左)高度:"), USpinBox);

    QDoubleSpinBox* VSpinBox = new QDoubleSpinBox();
    VSpinBox->setRange(0, 10000);
    VSpinBox->setValue(m_X4);
    formLayout.addRow(tr("左拼接缝区域(右)左上角横坐标:"), VSpinBox);

    QDoubleSpinBox* WSpinBox = new QDoubleSpinBox();
    WSpinBox->setRange(0, 10000);
    WSpinBox->setValue(m_Y4);
    formLayout.addRow(tr("左拼接缝区域(右)左上角纵坐标:"), WSpinBox);

    QDoubleSpinBox* XSpinBox = new QDoubleSpinBox();
    XSpinBox->setRange(0, 10000);
    XSpinBox->setValue(m_W4);
    formLayout.addRow(tr("左拼接缝区域(右)宽度:"), XSpinBox);

    QDoubleSpinBox* YSpinBox = new QDoubleSpinBox();
    YSpinBox->setRange(0, 10000);
    YSpinBox->setValue(m_H4);
    formLayout.addRow(tr("左拼接缝区域(右)高度:"), YSpinBox);

    QDoubleSpinBox* ZSpinBox = new QDoubleSpinBox();
    ZSpinBox->setRange(0, 10000);
    ZSpinBox->setValue(m_X5);
    formLayout.addRow(tr("右拼接缝区域(左)左上角横坐标:"), ZSpinBox);

    QDoubleSpinBox* AASpinBox = new QDoubleSpinBox();
    AASpinBox->setRange(0, 10000);
    AASpinBox->setValue(m_Y5);
    formLayout.addRow(tr("右拼接缝区域(左)左上角纵坐标:"), AASpinBox);

    QDoubleSpinBox* ABSpinBox = new QDoubleSpinBox();
    ABSpinBox->setRange(0, 10000);
    ABSpinBox->setValue(m_W5);
    formLayout.addRow(tr("右拼接缝区域(左)宽度:"), ABSpinBox);

    QDoubleSpinBox* ACSpinBox = new QDoubleSpinBox();
    ACSpinBox->setRange(0, 10000);
    ACSpinBox->setValue(m_H5);
    formLayout.addRow(tr("右拼接缝区域(左)高度:"), ACSpinBox);

    QDoubleSpinBox* ADSpinBox = new QDoubleSpinBox();
    ADSpinBox->setRange(0, 10000);
    ADSpinBox->setValue(m_X6);
    formLayout.addRow(tr("右拼接缝区域(右)左上角横坐标:"), ADSpinBox);

    QDoubleSpinBox* AESpinBox = new QDoubleSpinBox();
    AESpinBox->setRange(0, 10000);
    AESpinBox->setValue(m_Y6);
    formLayout.addRow(tr("右拼接缝区域(右)左上角纵坐标:"), AESpinBox);

    QDoubleSpinBox* AFSpinBox = new QDoubleSpinBox();
    AFSpinBox->setRange(0, 10000);
    AFSpinBox->setValue(m_W6);
    formLayout.addRow(tr("右拼接缝区域(右)宽度:"), AFSpinBox);

    QDoubleSpinBox* AGSpinBox = new QDoubleSpinBox();
    AGSpinBox->setRange(0, 10000);
    AGSpinBox->setValue(m_H6);
    formLayout.addRow(tr("右拼接缝区域(右)高度:"), AGSpinBox);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    formLayout.addRow(&buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        m_centerBrightnessLimit = ASpinBox->value();
        m_joint1BrightnessLimit = BSpinBox->value();
        m_joint2BrightnessLimit = CSpinBox->value();
        m_centerRGLimit = DSpinBox->value();
        m_joint1RGLimit = ESpinBox->value();
        m_joint2RGLimit = FSpinBox->value();
        m_centerBGLimit = GSpinBox->value();
        m_joint1BGLimit = HSpinBox->value();
        m_joint2BGLimit = ISpinBox->value();
        m_X1 = JSpinBox->value();
        m_Y1 = KSpinBox->value();
        m_W1 = LSpinBox->value();
        m_H1 = MSpinBox->value();
        m_X2 = NSpinBox->value();
        m_Y2 = OSpinBox->value();
        m_W2 = PSpinBox->value();
        m_H2 = QSpinBox->value();
        m_X3 = RSpinBox->value();
        m_Y3 = SSpinBox->value();
        m_W3 = TSpinBox->value();
        m_H3 = USpinBox->value();
        m_X4 = VSpinBox->value();
        m_Y4 = WSpinBox->value();
        m_W4 = XSpinBox->value();
        m_H4 = YSpinBox->value();
        m_X5 = ZSpinBox->value();
        m_Y5 = AASpinBox->value();
        m_W5 = ABSpinBox->value();
        m_H5 = ACSpinBox->value();
        m_X6 = ADSpinBox->value();
        m_Y6 = AESpinBox->value();
        m_W6 = AFSpinBox->value();
        m_H6 = AGSpinBox->value();
    }

    m_centerResultLabel->setText("暂无中心区域判断");
    m_joint1ResultLabel->setText("暂无左拼接缝判断");
    m_joint2ResultLabel->setText("暂无右拼接缝判断");
    m_centerLabel1->setText("中心区域显示区");
    m_centerLabel2->setText("中心区域显示区");
    m_joint1Label1->setText("左拼接缝显示区");
    m_joint1Label2->setText("左拼接缝显示区");
    m_joint2Label1->setText("右拼接缝显示区");
    m_joint2Label2->setText("右拼接缝显示区");
    m_centerBrightnessResultLabel->setText("中心区域亮度测试数据结果显示区");
    m_joint1BrightnessResultLabel->setText("左拼接缝亮度测试数据结果显示区");
    m_joint2BrightnessResultLabel->setText("右拼接缝亮度测试数据结果显示区");
    m_centerColorResultLabel->setText("中心区域色彩测试数据结果显示区");
    m_joint1ColorResultLabel->setText("左拼接缝色彩测试数据结果显示区");
    m_joint2ColorResultLabel->setText("右拼接缝色彩测试数据结果显示区");
}

// 打开中心区域图片函数
void MainWindow::openCenterImage()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                          tr("打开图片"),
                                                          ".",
                                                          tr("图片类型 (*.png *.jpg *.bmp)"));//弹出文件对话框，获取用户选择的图像文件名

    if (fileNames.count() < 2)//如果选择的图片数量小于2，则弹出错误对话框，并返回
    {
        QMessageBox::information(this,
                                 tr("打开错误"),
                                 tr("请选择至少两张图片"));
        return;
    }

    QString fileName1 = fileNames.at(0);//获取第一张图片的文件名
    QString fileName2 = fileNames.at(1);//获取第二张图片的文件名

    QImage image1(fileName1);//加载第一张图像文件
    if (image1.isNull())
    {
        QMessageBox::information(this,
                                 tr("打开错误"),
                                 tr("加载失败 %1.").arg(fileName1));//如果加载失败，则弹出错误对话框，并返回
        return;
    }

    QImage image2(fileName2);//加载第二张图像文件
    if (image2.isNull())
    {
        QMessageBox::information(this,
                                 tr("打开错误"),
                                 tr("加载失败 %1.").arg(fileName2));//如果加载失败，则弹出错误对话框，并返回
        return;
    }

    m_image1 = image1;//将加载的第一张图像存储到成员变量m_image1中
    m_image2 = image2;//将加载的第二张图像存储到成员变量m_image2中

    m_image1Copy = m_image1.copy();
    m_image2Copy = m_image2.copy();

}

// 打开拼接区域1图片函数
void MainWindow::openJoint1Image()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                          tr("打开图片"),
                                                          ".",
                                                          tr("图片类型 (*.png *.jpg *.bmp)"));//弹出文件对话框，获取用户选择的图像文件名

    if (fileNames.count() < 2)//如果选择的图片数量小于2，则弹出错误对话框，并返回
    {
        QMessageBox::information(this,
                                 tr("打开错误"),
                                 tr("请选择至少两张图片"));
        return;
    }

    QString fileName1 = fileNames.at(0);//获取第一张图片的文件名
    QString fileName2 = fileNames.at(1);//获取第二张图片的文件名

    QImage image1(fileName1);//加载第一张图像文件
    if (image1.isNull())
    {
        QMessageBox::information(this,
                                 tr("打开错误"),
                                 tr("加载失败 %1.").arg(fileName1));//如果加载失败，则弹出错误对话框，并返回
        return;
    }

    QImage image2(fileName2);//加载第二张图像文件
    if (image2.isNull())
    {
        QMessageBox::information(this,
                                 tr("打开错误"),
                                 tr("加载失败 %1.").arg(fileName2));//如果加载失败，则弹出错误对话框，并返回
        return;
    }

    m_image3 = image1;//将加载的第一张图像存储到成员变量m_image3中
    m_image4 = image2;//将加载的第二张图像存储到成员变量m_image4中

    m_image3Copy = m_image3.copy();
    m_image4Copy = m_image4.copy();

}

// 打开拼接区域2图片函数
void MainWindow::openJoint2Image()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                          tr("打开图片"),
                                                          ".",
                                                          tr("图片类型 (*.png *.jpg *.bmp)"));//弹出文件对话框，获取用户选择的图像文件名

    if (fileNames.count() < 2)//如果选择的图片数量小于2，则弹出错误对话框，并返回
    {
        QMessageBox::information(this,
                                 tr("打开错误"),
                                 tr("请选择至少两张图片"));
        return;
    }

    QString fileName1 = fileNames.at(0);//获取第一张图片的文件名
    QString fileName2 = fileNames.at(1);//获取第二张图片的文件名

    QImage image1(fileName1);//加载第一张图像文件
    if (image1.isNull())
    {
        QMessageBox::information(this,
                                 tr("打开错误"),
                                 tr("加载失败 %1.").arg(fileName1));//如果加载失败，则弹出错误对话框，并返回
        return;
    }

    QImage image2(fileName2);//加载第二张图像文件
    if (image2.isNull())
    {
        QMessageBox::information(this,
                                 tr("打开错误"),
                                 tr("加载失败 %1.").arg(fileName2));//如果加载失败，则弹出错误对话框，并返回
        return;
    }

    m_image5 = image1;//将加载的第一张图像存储到成员变量m_image5中
    m_image6 = image2;//将加载的第二张图像存储到成员变量m_image6中

    m_image5Copy = m_image5.copy();
    m_image6Copy = m_image6.copy();

}

// 标记中心区域图片函数
void MainWindow::markCenterImageRegions()
{
    //标记中心区域
    QPainter painter1(&m_image1Copy);//使用QPainter对象对图像进行绘制
    painter1.setPen(Qt::red);//设置画笔为红色
    painter1.setBrush(Qt::NoBrush);//设置画刷为空画刷
    painter1.drawRect(m_X1, m_Y1, m_W1, m_H1);
    QPixmap pixmap1 = QPixmap::fromImage(m_image1Copy);
    QSize size = this->size();
    pixmap1 = pixmap1.scaled(size / 4.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_centerLabel1->setPixmap(pixmap1);//将图像缩放成合适的大小，并将其显示在标签控件m_centerLabel1中

    QPainter painter2(&m_image2Copy);//使用QPainter对象对图像进行绘制
    painter2.setPen(Qt::red);//设置画笔为红色
    painter2.drawRect(m_X2, m_Y2, m_W2, m_H2);
    QPixmap pixmap2 = QPixmap::fromImage(m_image2Copy);
    pixmap2 = pixmap2.scaled(size / 4.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_centerLabel2->setPixmap(pixmap2);//将图像缩放成合适的大小，并将其显示在标签控件m_centerLabel2中

    m_centerBrightnessResultLabel->setText("");
    m_centerColorResultLabel->setText("");
    m_centerResultLabel->setText("");
    for (int i = 0; i < 2; i++)//将计算值置零
    {
        m_centerbrightness[i] = 0.0; // 中心区域平均亮度计算结果置零
        m_centerRG[i] = 0.0; // 中心区域R/G计算结果置零
        m_centerBG[i] = 0.0; // 中心区域B/G计算结果置零
    }
}

// 标记拼接区域1图片函数
void MainWindow::markJoint1ImageRegions()
{
    //标记拼接区域1
    QPainter painter3(&m_image3Copy);//使用QPainter对象对图像进行绘制
    painter3.setPen(Qt::blue);//设置画笔为蓝色
    painter3.setBrush(Qt::NoBrush);//设置画刷为空画刷
    painter3.drawRect(m_X3, m_Y3, m_W3, m_H3);
    QPixmap pixmap3 = QPixmap::fromImage(m_image3Copy);
    QSize size = this->size();
    pixmap3 = pixmap3.scaled(size / 4.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_joint1Label1->setPixmap(pixmap3);//将图像缩放成合适的大小，并将其显示在标签控件m_joint1Label1中

    QPainter painter4(&m_image4Copy);//使用QPainter对象对图像进行绘制
    painter4.setPen(Qt::blue);//设置画笔为蓝色
    painter4.drawRect(m_X4, m_Y4, m_W4, m_H4);
    QPixmap pixmap4 = QPixmap::fromImage(m_image4Copy);
    pixmap4 = pixmap4.scaled(size / 4.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_joint1Label2->setPixmap(pixmap4);//将图像缩放成合适的大小，并将其显示在标签控件m_joint1Label2中

    m_joint1BrightnessResultLabel->setText("");
    m_joint1ColorResultLabel->setText("");
    m_joint1ResultLabel->setText("");
    for (int i = 0; i < 2; i++)//将计算值置零
    {
        m_joint1brightness[i] = 0.0; // 拼接区域1平均亮度计算结果置零
        m_joint1RG[i] = 0.0; // 拼接区域1R/G计算结果置零
        m_joint1BG[i] = 0.0; // 拼接区域1B/G计算结果置零
    }
}

// 标记拼接区域2图片函数
void MainWindow::markJoint2ImageRegions()
{
    //标记拼接区域2
    QPainter painter5(&m_image5Copy);//使用QPainter对象对图像进行绘制
    painter5.setPen(Qt::green);//设置画笔为绿色
    painter5.setBrush(Qt::NoBrush);//设置画刷为空画刷
    painter5.drawRect(m_X5, m_Y5, m_W5, m_H5);
    QPixmap pixmap5 = QPixmap::fromImage(m_image5Copy);
    QSize size = this->size();
    pixmap5 = pixmap5.scaled(size / 4.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_joint2Label1->setPixmap(pixmap5);//将图像缩放成合适的大小，并将其显示在标签控件m_joint2Label1中

    QPainter painter6(&m_image6Copy);//使用QPainter对象对图像进行绘制
    painter6.setPen(Qt::green);//设置画笔为绿色
    painter6.drawRect(m_X6, m_Y6, m_W6, m_H6);
    QPixmap pixmap6 = QPixmap::fromImage(m_image6Copy);
    pixmap6 = pixmap6.scaled(size / 4.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_joint2Label2->setPixmap(pixmap6);//将图像缩放成合适的大小，并将其显示在标签控件m_joint2Label2中

    m_joint2BrightnessResultLabel->setText("");
    m_joint2ColorResultLabel->setText("");
    m_joint2ResultLabel->setText("");
    for (int i = 0; i < 2; i++)//将计算值置零
    {
        m_joint2brightness[i] = 0.0; // 拼接区域2平均亮度计算结果置零
        m_joint2RG[i] = 0.0; // 拼接区域2R/G计算结果置零
        m_joint2BG[i] = 0.0; // 拼接区域2B/G计算结果置零
    }
}

// 计算并输出中心区域结果函数
void MainWindow::CenterCalculate()
{
    if (m_image1.isNull() || m_image2.isNull())
    {
        QMessageBox::information(this,
                                 tr("计算出错"),
                                 tr("未选择中心区域图片"));
        return;
    }

    calculateCenterBrightness(); // 计算并判断亮度
    calculateCenterColor(); // 计算并判断色彩
    QString brightnessResultText = tr("中心区域平均亮度: <br>"
                                      "中心区域(左)(红)平均亮度: %1<br>"
                                      "中心区域(右)(红)平均亮度: %2<br>")
                                       .arg(QString::number(m_centerbrightness[0], 'f', 4))
                                       .arg(QString::number(m_centerbrightness[1], 'f', 4));
    m_centerBrightnessResultLabel->setText(brightnessResultText);

    QString colorResultText = tr("中心区域平均RGB值: <br>"
                                 "中心区域(左)(红)R: %1 "
                                 "G: %2 "
                                 "B: %3 <br>"
                                 "中心区域(右)(红)R: %4 "
                                 "G: %5 "
                                 "B: %6 <br>")
                                  .arg(QString::number(centerBgr1.val[2], 'f', 4))
                                  .arg(QString::number(centerBgr1.val[1], 'f', 4))
                                  .arg(QString::number(centerBgr1.val[0], 'f', 4))
                                  .arg(QString::number(centerBgr2.val[2], 'f', 4))
                                  .arg(QString::number(centerBgr2.val[1], 'f', 4))
                                  .arg(QString::number(centerBgr2.val[0], 'f', 4));
    m_centerColorResultLabel->setText(colorResultText);

    QString judgeText;
    if (CenterbrightnessPass) {
        judgeText = tr("<span style='font-size:15px'><br><br>中心区域亮度判定结果: 合格");
    } else {
        judgeText = tr("<span style='font-size:15px'><br><br>中心区域亮度判定结果: 不合格");
    }
    if (CenterRGPass) {
        judgeText += tr("<span style='font-size:15px'><br><br>中心区域R/G判定结果: 合格");
    } else {
        judgeText += tr("<span style='font-size:15px'><br><br>中心区域R/G判定结果: 不合格");
    }
    if (CenterBGPass) {
        judgeText += tr("<span style='font-size:15px'><br><br>中心区域B/G判定结果: 合格");
    } else {
        judgeText += tr("<span style='font-size:15px'><br><br>中心区域B/G判定结果: 不合格");
    }
    m_centerResultLabel->setText(judgeText);
}

// 计算并输出拼接区域1结果函数
void MainWindow::Joint1Calculate()
{
    if (m_image3.isNull() || m_image4.isNull())
    {
        QMessageBox::information(this,
                                 tr("计算出错"),
                                 tr("未选择左拼接缝图片"));
        return;
    }

    calculateJoint1Brightness(); // 计算并判断亮度
    calculateJoint1Color(); // 计算并判断色彩
    QString brightnessResultText = tr("左拼接缝平均亮度: <br>"
                                      "左拼接缝区域(左)(蓝)平均亮度: %1<br>"
                                      "左拼接缝区域(右)(蓝)平均亮度: %2<br>")
                                       .arg(QString::number(m_joint1brightness[0], 'f', 4))
                                       .arg(QString::number(m_joint1brightness[1], 'f', 4));
    m_joint1BrightnessResultLabel->setText(brightnessResultText);

    QString colorResultText = tr("左拼接缝平均RGB值: <br>"
                                 "左拼接缝(左)(蓝)R: %1 "
                                 "G: %2 "
                                 "B: %3 <br>"
                                 "左拼接缝(右)(蓝)R: %4 "
                                 "G: %5 "
                                 "B: %6 <br>")
                                  .arg(QString::number(joint1Bgr1.val[2], 'f', 4))
                                  .arg(QString::number(joint1Bgr1.val[1], 'f', 4))
                                  .arg(QString::number(joint1Bgr1.val[0], 'f', 4))
                                  .arg(QString::number(joint1Bgr2.val[2], 'f', 4))
                                  .arg(QString::number(joint1Bgr2.val[1], 'f', 4))
                                  .arg(QString::number(joint1Bgr2.val[0], 'f', 4));
    m_joint1ColorResultLabel->setText(colorResultText);

    QString judgeText;
    if (Joint1brightnessPass) {
        judgeText = tr("<span style='font-size:15px'><br><br>左拼接缝亮度判定结果: 合格");
    } else {
        judgeText = tr("<span style='font-size:15px'><br><br>左拼接缝亮度判定结果: 不合格");
    }
    if (Joint1RGPass) {
        judgeText += tr("<span style='font-size:15px'><br><br>左拼接缝R/G判定结果: 合格");
    } else {
        judgeText += tr("<span style='font-size:15px'><br><br>左拼接缝R/G判定结果: 不合格");
    }
    if (Joint1BGPass) {
        judgeText += tr("<span style='font-size:15px'><br><br>左拼接缝B/G判定结果: 合格");
    } else {
        judgeText += tr("<span style='font-size:15px'><br><br>左拼接缝B/G判定结果: 不合格");
    }
    m_joint1ResultLabel->setText(judgeText);
}

// 计算并输出拼接区域2结果函数
void MainWindow::Joint2Calculate()
{
    if (m_image5.isNull() || m_image6.isNull())
    {
        QMessageBox::information(this,
                                 tr("计算出错"),
                                 tr("未选择右拼接缝图片"));
        return;
    }

    calculateJoint2Brightness(); // 计算并判断亮度
    calculateJoint2Color(); // 计算并判断色彩
    QString brightnessResultText = tr("右拼接缝平均亮度: <br>"
                                      "右拼接缝区域(左)(蓝)平均亮度: %1<br>"
                                      "右拼接缝区域(右)(蓝)平均亮度: %2<br>")
                                       .arg(QString::number(m_joint2brightness[0], 'f', 4))
                                       .arg(QString::number(m_joint2brightness[1], 'f', 4));
    m_joint2BrightnessResultLabel->setText(brightnessResultText);

    QString colorResultText = tr("右拼接缝平均RGB值: <br>"
                                 "右拼接缝(左)(绿)R: %1 "
                                 "G: %2 "
                                 "B: %3 <br>"
                                 "右拼接缝(右)(绿)R: %4 "
                                 "G: %5 "
                                 "B: %6 <br>")
                                  .arg(QString::number(joint2Bgr1.val[2], 'f', 4))
                                  .arg(QString::number(joint2Bgr1.val[1], 'f', 4))
                                  .arg(QString::number(joint2Bgr1.val[0], 'f', 4))
                                  .arg(QString::number(joint2Bgr2.val[2], 'f', 4))
                                  .arg(QString::number(joint2Bgr2.val[1], 'f', 4))
                                  .arg(QString::number(joint2Bgr2.val[0], 'f', 4));
    m_joint2ColorResultLabel->setText(colorResultText);

    QString judgeText;
    if (Joint2brightnessPass) {
        judgeText = tr("<span style='font-size:15px'><br><br>右拼接缝亮度判定结果: 合格");
    } else {
        judgeText = tr("<span style='font-size:15px'><br><br>右拼接缝亮度判定结果: 不合格");
    }
    if (Joint2RGPass) {
        judgeText += tr("<span style='font-size:15px'><br><br>右拼接缝R/G判定结果: 合格");
    } else {
        judgeText += tr("<span style='font-size:15px'><br><br>右拼接缝R/G判定结果: 不合格");
    }
    if (Joint2BGPass) {
        judgeText += tr("<span style='font-size:15px'><br><br>右拼接缝B/G判定结果: 合格");
    } else {
        judgeText += tr("<span style='font-size:15px'><br><br>右拼接缝B/G判定结果: 不合格");
    }
    m_joint2ResultLabel->setText(judgeText);
}

// 计算并判断中心区域亮度函数
void MainWindow::calculateCenterBrightness()
{
    // 读取图像灰度值
    cv::Mat matImage1 = cv::Mat(m_image1.height(), m_image1.width(), CV_8UC4, (uchar*)m_image1.constBits(), m_image1.bytesPerLine());
    cv::Mat matImage2 = cv::Mat(m_image2.height(), m_image2.width(), CV_8UC4, (uchar*)m_image2.constBits(), m_image2.bytesPerLine());
    cv::Mat grayImage1;
    cv::Mat grayImage2;
    cv::cvtColor(matImage1, grayImage1, cv::COLOR_BGRA2GRAY);
    cv::cvtColor(matImage2, grayImage2, cv::COLOR_BGRA2GRAY);
    cv::Scalar mean1, mean2;
    // 计算图像平均亮度值
    cv::Rect roi(m_X1, m_Y1, m_W1, m_H1);
    mean1 = cv::mean(grayImage1(roi));
    roi = cv::Rect(m_X2, m_Y2, m_W2, m_H2);
    mean2 = cv::mean(grayImage2(roi));
    m_centerbrightness[0] = mean1.val[0];
    m_centerbrightness[1] = mean2.val[0];
    // 判断亮度值是否合格
    double centerBrightnessDiff = std::abs(m_centerbrightness[0] - m_centerbrightness[1]);

    if (centerBrightnessDiff > m_centerBrightnessLimit)
    {
        CenterbrightnessPass = false;
    }
    else {
        CenterbrightnessPass = true;
    }
}

// 计算并判断中心区域色彩函数
void MainWindow::calculateCenterColor()
{
    // 读取图像RGB值
    cv::Mat matImage1 = cv::Mat(m_image1.height(), m_image1.width(), CV_8UC4, (uchar*)m_image1.constBits(), m_image1.bytesPerLine());
    cv::Mat matImage2 = cv::Mat(m_image2.height(), m_image2.width(), CV_8UC4, (uchar*)m_image2.constBits(), m_image2.bytesPerLine());
    // 计算图像平均RGB值
    centerBgr1 = cv::mean(matImage1(cv::Rect(m_X1, m_Y1, m_W1, m_H1)));
    centerBgr2 = cv::mean(matImage2(cv::Rect(m_X2, m_Y2, m_W2, m_H2)));
    // 计算图像R/G、B/G
    double centerR1 = centerBgr1.val[2];
    double centerG1 = centerBgr1.val[1];
    double centerB1 = centerBgr1.val[0];
    double centerR2 = centerBgr2.val[2];
    double centerG2 = centerBgr2.val[1];
    double centerB2 = centerBgr2.val[0];
    m_centerRG[0] = centerR1 / centerG1;
    m_centerRG[1] = centerR2 / centerG2;
    m_centerBG[0] = centerB1 / centerG1;
    m_centerBG[1] = centerB2 / centerG2;

    //判断R/G是否合格
    if (abs(m_centerRG[0] - m_centerRG[1]) > m_centerRGLimit)
    {
        CenterRGPass = false;
    }
    else
    {
        CenterRGPass = true;
    }

    //判断B/G是否合格
    if (abs(m_centerBG[0] - m_centerBG[1]) > m_centerBGLimit)
    {
        CenterBGPass = false;
    }
    else
    {
        CenterBGPass = true;
    }
}

// 计算并判断拼接区域1亮度函数
void MainWindow::calculateJoint1Brightness()
{
    // 读取图像灰度值
    cv::Mat matImage3 = cv::Mat(m_image3.height(), m_image3.width(), CV_8UC4, (uchar*)m_image3.constBits(), m_image3.bytesPerLine());
    cv::Mat matImage4 = cv::Mat(m_image4.height(), m_image4.width(), CV_8UC4, (uchar*)m_image4.constBits(), m_image4.bytesPerLine());
    cv::Mat grayImage3;
    cv::Mat grayImage4;
    cv::cvtColor(matImage3, grayImage3, cv::COLOR_BGRA2GRAY);
    cv::cvtColor(matImage4, grayImage4, cv::COLOR_BGRA2GRAY);
    cv::Scalar mean3, mean4;
    // 计算图像平均亮度值
    cv::Rect roi(m_X3, m_Y3, m_W3, m_H3);
    mean3 = cv::mean(grayImage3(roi));
    roi = cv::Rect(m_X4, m_Y4, m_W4, m_H4);
    mean4 = cv::mean(grayImage4(roi));
    m_joint1brightness[0] = mean3.val[0];
    m_joint1brightness[1] = mean4.val[0];
    // 判断亮度值是否合格
    double joint1BrightnessDiff = std::abs(m_joint1brightness[0] - m_joint1brightness[1]);

    if (joint1BrightnessDiff > m_joint1BrightnessLimit)
    {
        Joint1brightnessPass = false;
    }
    else {
        Joint1brightnessPass = true;
    }
}

// 计算并判断拼接区域1色彩函数
void MainWindow::calculateJoint1Color()
{
    // 读取图像RGB值
    cv::Mat matImage3 = cv::Mat(m_image3.height(), m_image3.width(), CV_8UC4, (uchar*)m_image3.constBits(), m_image3.bytesPerLine());
    cv::Mat matImage4 = cv::Mat(m_image4.height(), m_image4.width(), CV_8UC4, (uchar*)m_image4.constBits(), m_image4.bytesPerLine());
    // 计算图像平均RGB值
    joint1Bgr1 = cv::mean(matImage3(cv::Rect(m_X3, m_Y3, m_W3, m_H3)));
    joint1Bgr2 = cv::mean(matImage4(cv::Rect(m_X4, m_Y4, m_W4, m_H4)));
    // 计算图像R/G、B/G
    double joint1R1 = joint1Bgr1.val[2];
    double joint1G1 = joint1Bgr1.val[1];
    double joint1B1 = joint1Bgr1.val[0];
    double joint1R2 = joint1Bgr2.val[2];
    double joint1G2 = joint1Bgr2.val[1];
    double joint1B2 = joint1Bgr2.val[0];
    m_joint1RG[0] = joint1R1 / joint1G1;
    m_joint1RG[1] = joint1R2 / joint1G2;
    m_joint1BG[0] = joint1B1 / joint1G1;
    m_joint1BG[1] = joint1B2 / joint1G2;

    //判断R/G是否合格
    if (abs(m_joint1RG[0] - m_joint1RG[1]) > m_joint1RGLimit)
    {
        Joint1RGPass = false;
    }
    else
    {
        Joint1RGPass = true;
    }

    //判断B/G是否合格
    if (abs(m_joint1BG[0] - m_joint1BG[1]) > m_joint1BGLimit)
    {
        Joint1BGPass = false;
    }
    else
    {
        Joint1BGPass = true;
    }
}

// 计算并判断拼接区域2亮度函数
void MainWindow::calculateJoint2Brightness()
{
    // 读取图像灰度值
    cv::Mat matImage5 = cv::Mat(m_image5.height(), m_image5.width(), CV_8UC4, (uchar*)m_image5.constBits(), m_image5.bytesPerLine());
    cv::Mat matImage6 = cv::Mat(m_image6.height(), m_image6.width(), CV_8UC4, (uchar*)m_image6.constBits(), m_image6.bytesPerLine());
    cv::Mat grayImage5;
    cv::Mat grayImage6;
    cv::cvtColor(matImage5, grayImage5, cv::COLOR_BGRA2GRAY);
    cv::cvtColor(matImage6, grayImage6, cv::COLOR_BGRA2GRAY);
    cv::Scalar mean5, mean6;
    // 计算图像平均亮度值
    cv::Rect roi(m_X5, m_Y5, m_W5, m_H5);
    mean5 = cv::mean(grayImage5(roi));
    roi = cv::Rect(m_X6, m_Y6, m_W6, m_H6);
    mean6 = cv::mean(grayImage6(roi));
    m_joint2brightness[0] = mean5.val[0];
    m_joint2brightness[1] = mean6.val[0];
    // 判断亮度值是否合格
    double joint2BrightnessDiff = std::abs(m_joint2brightness[0] - m_joint2brightness[1]);

    if (joint2BrightnessDiff > m_joint2BrightnessLimit)
    {
        Joint2brightnessPass = false;
    }
    else {
        Joint2brightnessPass = true;
    }
}

// 计算并判断拼接区域2色彩函数
void MainWindow::calculateJoint2Color()
{
    // 读取图像RGB值
    cv::Mat matImage5 = cv::Mat(m_image5.height(), m_image5.width(), CV_8UC4, (uchar*)m_image5.constBits(), m_image5.bytesPerLine());
    cv::Mat matImage6 = cv::Mat(m_image6.height(), m_image6.width(), CV_8UC4, (uchar*)m_image6.constBits(), m_image6.bytesPerLine());
    // 计算图像平均RGB值
    joint2Bgr1 = cv::mean(matImage5(cv::Rect(m_X5, m_Y5, m_W5, m_H5)));
    joint2Bgr2 = cv::mean(matImage6(cv::Rect(m_X6, m_Y6, m_W6, m_H6)));
    // 计算图像R/G、B/G
    double joint2R1 = joint2Bgr1.val[2];
    double joint2G1 = joint2Bgr1.val[1];
    double joint2B1 = joint2Bgr1.val[0];
    double joint2R2 = joint2Bgr2.val[2];
    double joint2G2 = joint2Bgr2.val[1];
    double joint2B2 = joint2Bgr2.val[0];
    m_joint2RG[0] = joint2R1 / joint2G1;
    m_joint2RG[1] = joint2R2 / joint2G2;
    m_joint2BG[0] = joint2B1 / joint2G1;
    m_joint2BG[1] = joint2B2 / joint2G2;

    //判断R/G是否合格
    if (abs(m_joint2RG[0] - m_joint2RG[1]) > m_joint2RGLimit)
    {
        Joint2RGPass = false;
    }
    else
    {
        Joint2RGPass = true;
    }

    //判断B/G是否合格
    if (abs(m_joint2BG[0] - m_joint2BG[1]) > m_joint2BGLimit)
    {
        Joint2BGPass = false;
    }
    else
    {
        Joint2BGPass = true;
    }
}

// 保存文本结果函数
void MainWindow::saveResultTextToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    tr("保存测试结果文本"),
                                                    "",
                                                    tr("文本文件 (*.txt)"));
    if (filePath.isEmpty()) {
        return;
    }

    // 将所有的<br>替换为回车，同时去除所有<span>标签
    QString label1Result = m_centerBrightnessResultLabel->text();
    QString label2Result = m_centerColorResultLabel->text();
    QString label3Result = m_centerResultLabel->text();
    label1Result.replace("<br>", "\n");
    label2Result.replace("<br>", "\n");
    label3Result.replace("<br>", "\n");
    label3Result.remove(QRegularExpression("<span.*?>"));

    QString label4Result = m_joint1BrightnessResultLabel->text();
    QString label5Result = m_joint1ColorResultLabel->text();
    QString label6Result = m_joint1ResultLabel->text();
    label4Result.replace("<br>", "\n");
    label5Result.replace("<br>", "\n");
    label6Result.replace("<br>", "\n");
    label6Result.remove(QRegularExpression("<span.*?>"));

    QString label7Result = m_joint2BrightnessResultLabel->text();
    QString label8Result = m_joint2ColorResultLabel->text();
    QString label9Result = m_joint2ResultLabel->text();
    label7Result.replace("<br>", "\n");
    label8Result.replace("<br>", "\n");
    label9Result.replace("<br>", "\n");
    label9Result.remove(QRegularExpression("<span.*?>"));

    // 打开文件并写入结果
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << label1Result << "\n\n";
        out << label2Result << "\n\n";
        out << label3Result << "\n\n";
        out << label4Result << "\n\n";
        out << label5Result << "\n\n";
        out << label6Result << "\n\n";
        out << label7Result << "\n\n";
        out << label8Result << "\n\n";
        out << label9Result << "\n\n";
        file.close();
    }
}

// 保存图片结果函数
void MainWindow::saveMarkedImageToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存标记图片"), "", tr("图片文件 (*.png *.jpg *.bmp)"));//选择保存路径和文件名
    if (!fileName.isEmpty())
    {
        // 获取要保存的标记后图像
        QPixmap centerPixmap1 = *m_centerLabel1->pixmap();
        QPixmap centerPixmap2 = *m_centerLabel2->pixmap();
        QPixmap joint1Pixmap1 = *m_joint1Label1->pixmap();
        QPixmap joint1Pixmap2 = *m_joint1Label2->pixmap();
        QPixmap joint2Pixmap1 = *m_joint2Label1->pixmap();
        QPixmap joint2Pixmap2 = *m_joint2Label2->pixmap();

        // 保存标记后的图像
        bool success = false;
        QString format = QFileInfo(fileName).suffix().toLower();//获取文件后缀
        if (format == "png")
        {
            success = centerPixmap1.save(fileName + "_标记中心区域图(左).png", "PNG") && centerPixmap2.save(fileName + "_标记中心区域图(右).png", "PNG") &&
                                 joint1Pixmap1.save(fileName + "_标记左拼接缝图(左).png", "PNG") && joint1Pixmap2.save(fileName + "_标记左拼接缝图(右).png", "PNG") &&
                                 joint2Pixmap1.save(fileName + "_标记右拼接缝图(左).png", "PNG") && joint2Pixmap2.save(fileName + "_标记右拼接缝图(右).png", "PNG");
        }
        else if (format == "jpg" || format == "jpeg")
        {
            success = centerPixmap1.save(fileName + "_标记中心区域图(左).jpg", "JPGE") && centerPixmap2.save(fileName + "_标记中心区域图(右).jpg", "JPGE") &&
                                 joint1Pixmap1.save(fileName + "_标记左拼接缝图(左).jpg", "JPGE") && joint1Pixmap2.save(fileName + "_标记左拼接缝图(右).jpg", "JPGE") &&
                                 joint2Pixmap1.save(fileName + "_标记右拼接缝图(左).jpg", "JPGE") && joint2Pixmap2.save(fileName + "_标记右拼接缝图(右).jpg", "JPGE");
        }
        else if (format == "bmp")
        {
            success = centerPixmap1.save(fileName + "_标记中心区域图(左).bmp", "BMP") && centerPixmap2.save(fileName + "_标记中心区域图(右).bmp", "BMP") &&
                                 joint1Pixmap1.save(fileName + "_标记左拼接缝图(左).bmp", "BMP") && joint1Pixmap2.save(fileName + "_标记左拼接缝图(右).bmp", "BMP") &&
                                 joint2Pixmap1.save(fileName + "_标记右拼接缝图(左).bmp", "BMP") && joint2Pixmap2.save(fileName + "_标记右拼接缝图(右).bmp", "BMP");
        }
        if (!success)
        {
            QMessageBox::warning(this, tr("保存失败"), tr("未能保存图片 %1").arg(fileName));
        }
    }
}




