SELECT 
dbo.IPPatCost.DeptId,
dbo.IPPatCost.ChargeStandardId,
dbo.IPPatCost.DeptNm,
dbo.IPPatCost.FeeTypeNm,
dbo.IPPatCost.ChargeStandardNm,
Sum(dbo.IPPatCost.Quantity) 
FROM 
dbo.IPPatCost 
WHERE 
dbo.IPPatCost.ExeDt BETWEEN '2019-03-01' AND '2019-03-01' AND 
dbo.IPPatCost.FeeTypeId NOT IN (3,5) 
GROUP BY 
dbo.IPPatCost.DeptId,
dbo.IPPatCost.ChargeStandardId,
dbo.IPPatCost.DeptNm,
dbo.IPPatCost.FeeTypeNm,
dbo.IPPatCost.ChargeStandardNm