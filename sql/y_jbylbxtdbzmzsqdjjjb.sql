SELECT 
nhis.dbo._y_spsq.YYYBBYJ_SignDate,
nhis.dbo._y_spsq.Name,
nhis.dbo._y_spsq.DiseaseName,
nhis.dbo._y_spsq.Tel,
nhis.dbo._y_spsq.IdentificationNum,
nhis.dbo._y_spsq.Department,
nhis.dbo._y_spsq.AttendingPhysician_Sign,
nhis.dbo._y_spsq.ISUPLOAD,
nhis.dbo._y_spsq.RETIMES 

FROM 
nhis.dbo._y_spsq 
WHERE 
nhis.dbo._y_spsq.ID >= 0 AND 
ApprovalCategory = 14 