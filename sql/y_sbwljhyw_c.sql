SELECT TOP 1 
nhis.dbo.CasePageDataInfo.VisitId,
nhis.dbo.CasePageDataInfo.ParameterValue,
nhis.dbo.InVisit.InChgDocNm,
nhis.dbo.InVisit.Deptment 

FROM 
nhis.dbo.ZhaoQingInVisitSiReg 
INNER JOIN nhis.dbo.CasePageDataInfo ON nhis.dbo.ZhaoQingInVisitSiReg.VisitId = nhis.dbo.CasePageDataInfo.VisitId 
INNER JOIN nhis.dbo.InVisit ON nhis.dbo.ZhaoQingInVisitSiReg.VisitId = nhis.dbo.InVisit.InVisitId 
WHERE 
nhis.dbo.CasePageDataInfo.ParameterName = '联系人电话' AND 
nhis.dbo.ZhaoQingInVisitSiReg.YbId = '