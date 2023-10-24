-- https://school.programmers.co.kr/learn/courses/30/lessons/131536
SELECT user_id, product_id
FROM ONLINE_SALE
GROUP BY user_id, product_id
HAVING count(*) >= 2
ORDER BY user_id, product_id desc