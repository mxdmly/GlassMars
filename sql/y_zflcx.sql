SELECT 
nhis.dbo.InVisit.Name,
nhis.dbo.InVisit.OutDeptment,
nhis.dbo.InVisit.AdmitDT,
nhis.dbo.InVisit.DischargeDT,
nhis.dbo.IPBsnXmlSave.SumFee,
nhis.dbo.IPBsnXmlSave.BsnXml 

FROM 
nhis.dbo.IPBsnXmlSave 
INNER JOIN nhis.dbo.InVisit ON nhis.dbo.IPBsnXmlSave.VisitId = nhis.dbo.InVisit.InVisitId 
WHERE 
nhis.dbo.InVisit.OutDeptment NOT LIKE '%це%' AND 
nhis.dbo.InVisit.AdmitDT >= '2018-01-01' 
