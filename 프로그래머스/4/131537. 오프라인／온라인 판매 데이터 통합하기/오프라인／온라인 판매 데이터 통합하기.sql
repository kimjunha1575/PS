select
	date_format(sales_date, '%Y-%m-%d') as sd,
    product_id,
    user_id,
    sales_amount
from online_sale
where sales_date like '2022-03%'

union all

select
	date_format(sales_date, '%Y-%m-%d') as sd,
    product_id,
    NULL as user_id,
    sales_amount
from offline_sale
where sales_date like '2022-03%'


order by
	sd asc,
    product_id asc,
    user_id asc