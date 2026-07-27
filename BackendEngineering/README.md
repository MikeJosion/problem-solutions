# 后端

## 目录

---

## 一次Web请求的完整请求—响应流程

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/e07a5a4d-a509-40ba-a41e-372489b69a56/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8827%E6%97%A5_15_35_37.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB466Z7FAWKMH%2F20260727%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260727T143049Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEIb%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJGMEQCIAxaZGBEi4bhG%2F3QHAbkEVIw45OhCyfF5GADwUxKu0EfAiB4NX47DfdM3sHC7KQd5BCx3C8ShRY%2BIoPwfiyxCFS4Uir%2FAwhPEAAaDDYzNzQyMzE4MzgwNSIMVg66wdfpkPcZ2rBCKtwDikSieHoMQAMnjbQ8nxsgPtcq9Y%2Bv2LuEZR0kT6lvhEhV4K6D3mgfIiOkIIl7iqVa6ux87tfRZmifvELNExf5W53Bv02WpH7e3oQCdFwKK1Xnf%2FQkZeQa8PT27jK%2BQ2tvHpkb1xgnP7WsIRbobKpDzg59iMKRuWOZ3V4cwI9rdUbGeVgjqIdikpog6slVMb8%2Bk%2BuvIyUi99I%2Bn19fGSJ%2B6Vu4QP3HrbAYvFBS8qf%2FcwJ7F5OjjyLxIVbxm8NRoSwmn2GmHJPA%2FTjj6z7lvXq5t3o7ys43GRHJCtxQSewed0Y0397ds5EDmhVm%2F8qFrtO7tXeT55b8iImf05VlKX4neSTRoOG9g6QGVDHw1pHml8vLe9YsDfAAk7mOj31w3PXG%2BgFTpJRqggDAizcU%2BApxmBLoaZfWSyNmZbAP0wYiFvhJl3pGGxnnxCRb2bK%2FseY4eVfvT9ZYXFLHJLErLn8ukzfaDkJvBFxJtbBiINR5DZQ283D0qlumDph16KAbkrQ5H2ATF0%2Bq1j27pzxL8pF2AN7OOjlGcqmYyPU8f2OpcNRDnvdaSyi4oSXlmLfJA6JWyVo3hgIZsuyRzt8cDTOrWSgfuz8e5Ar5cnLzEdy5FD7mZlUaycCxiOWbjYww1Led0wY6pgGvOgMDqKNrgN4MprQZv1h5xK0g3FPgZRgzFmM74yvDqygUwyMhPO8QmbqM7RUREg2njstwi1KRmh73aS%2Fzb2hQqoBWNh6WIdc480JlpStmeOe2lsRvEqjt8AcHMdVrmMshyVTSZqiwezr1So8J48qcbIFMJ%2BaPud8943YiHMJd0zCd2YbYVUAYYETsejgCqE19fVx4hhtdDqizYAaGI5cgZBPpCrtW&X-Amz-Signature=81a84f0ed23d226fd68202c5a95b322841b37dce6340053850b629979c234dd1&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

1. 输入 URL / 发起请求
1. DNS 解析（域名 → IP）
1. 建立连接（TCP 三次握手 / TLS 握手）
1. 发送 HTTP 请求（请求行 / 请求头 / 请求体）
1. 服务端处理（路由 / 业务 / 数据库 / 缓存）
1. 返回 HTTP 响应（状态码 / 响应头 / 响应体）
1. 浏览器渲染（解析 / 布局 / 绘制）
1. 连接复用与关闭（Keep-Alive / 四次挥手）
