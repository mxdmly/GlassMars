﻿#ifndef X_DOC_H
#define X_DOC_H

#include <QObject>

class x_doc
{
public:
    x_doc();
    const QString docRe1400_str = "个人编号|单位编号|单位名称/户主名称|身份证号|姓名|性别|民族|出生日期|医疗人员类别|医疗证号|人员资料登记状态|参保状态|异地人员标志|统筹区号|基金类型|年度|在院状态|本年医疗费总金额累计|本年医保支付金额累计|本年进入统筹费用累计|本年进入补充医疗保险费用累计|本年起付标准累计|本年住院次数|本年超封顶线个人自付累计|本年进入结算费用累计|本年补充医保二次支付金额累计|参保类别|经办机构编码|经办机构名称|医疗待遇类别|报销类型|单位地址/家庭地址|是否五保供养|医疗类别|基本医疗本次支付限额|大病医疗本次支付限额|公务员本次支付限额|本年度基本医疗保险统筹基金累计支付金额|大病医疗统筹累计|普通门诊年度余额";
    const QString docRe1600_str = "审批标志|审批编号|就诊医院编号|就诊医院名称|就诊疾病编码|就诊疾病名称|开始时间|结束时间|备用|备用|备用";
    const QString docRe1710_str = "在院状态|个人编号|定点医疗机构编号|定点医疗机构名称|就诊流水号|医疗类别|入院日期|入院诊断疾病编码|入院诊断疾病名称|科室名称|床位号|医生代码|医生姓名|医院经办人|医院经办日期|备用|备用|备用";

    const QString sqlCel_str = "SELECT TOP 1 nhis.dbo.CasePageDataInfo.VisitId, nhis.dbo.CasePageDataInfo.ParameterValue FROM nhis.dbo.ZhaoQingInVisitSiReg INNER JOIN nhis.dbo.CasePageDataInfo ON nhis.dbo.ZhaoQingInVisitSiReg.VisitId = nhis.dbo.CasePageDataInfo.VisitId WHERE nhis.dbo.CasePageDataInfo.ParameterName = \'联系人电话\' AND nhis.dbo.ZhaoQingInVisitSiReg.YbId = \'";
};

#endif // X_DOC_H
