# 后端

## 目录

---

## 一次 Web 请求的完整流程（请求 → 响应）

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/e07a5a4d-a509-40ba-a41e-372489b69a56/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8827%E6%97%A5_15_35_37.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB466YYTZN6CE%2F20260730%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260730T021310Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEML%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQDlBGVB1J%2F8EmMeywsZvwokkbB55zcoJtuKCgnf%2B4JwvgIhAPxWmjKY2h7HEMqzg8wtdwNLXtMArHXdx6NhNsl7pC9xKogECIv%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQABoMNjM3NDIzMTgzODA1IgyG3qfD9p6aC9En6h0q3AOLa3nqae4dVLS%2BtVEwMxyvmiKNRacyEnS1HUfQjw2TEhO9HA1bjHZR%2FXb5BIs2CpDZM%2BK7OL1mmsEDDOCTTCSC7MN20et6P7jkBi8dp06jYEFA0AEuTNRO9fW4zDWn6DTnJkM65lWdBKZvTC3rav2TuljfwefRxt%2FKg9nu6fcopVuoMVcw0Xi9mauP2%2FTelQFlhLHK0AL7oNr4lIWeZ5Dgm914c1OTREsW7%2BdrLnnVp8hdQ0aFPR4DDtQofgZ0EMv4JjltvblRiN7ICVSFB8M%2BuFvBRjAN53jSydKwZyavABtkubTzAJz1I1bEUgEyGfyKa64xOzAoLRqmiVpzTTniEDdlFD2T%2F95DkcEFgXCYcxOzd7qRRh1QDKGjpVyLOOGtwajDG%2F36%2Fr8BuadBtEpguE9i06tTZIcoIVhnQxc0G2U9D8x0pB5EsmcXD9JJvBoh9m5QjNggInscfpIn36gIbOZukHe7qftBOuc9aBLxmLowA72jw5v%2FaDS6Y0HXSIbKx9HL8%2BCG5L9iSR7vPm6WoDn2Ya6j0jwhrH97PN9xnU%2F65TeCiPFWwFDHGj3ODJcVvqBXhCgvrwN7gQx89SvNLxDrdRIpPDp7mLI1TY0YzB8LzonvTrI0HIvymTDn36rTBjqkAd8ArOib8%2Bu4Q20oSFCH3Gv9Hr8G8MO4c3TlDFaKjUe7oVeU17GnxT6bCSG90vNEz7qLJKvEvV3peFkv8NybG5vE4w3N1RKCehT9BArCi686Sxeutc7L%2FC8%2BRB4rWzXiqp1j2533O0IM8fnXeVgEKYAhnzn%2B1SEycaCxCcFXfFU0hs0pd31igj9MJG5n168bSqidlWl16mXxQbO18n5UdmWGTa6c&X-Amz-Signature=d306dd0a1c87769b1dd2ff98adc6300a7e41fd7f7adbf8d3514a6ea14f5fa85a&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

**请求—响应全流程（速记）**

1. 输入 URL / 发起请求
1. DNS 解析（域名 → IP）
1. 建立连接（TCP 三次握手 / TLS 握手）
1. 发送 HTTP 请求（请求行 / 请求头 / 请求体）
1. 服务端处理（路由 / 业务 / 数据库 / 缓存）
1. 返回 HTTP 响应（状态码 / 响应头 / 响应体）
1. 浏览器渲染（解析 / 布局 / 绘制）
1. 连接复用与关闭（Keep-Alive / 四次挥手）
## HTTP 报文长什么样（请求 / 响应）

> **HTTP 报文组成**

> 

> - 请求（Request）= 请求行（方法 + 路径 + HTTP 版本） + 请求头 + 空行 + 请求体

> - 响应（Response）= 状态行（HTTP 版本 + 状态码 + 状态描述） + 响应头 + 空行 + 响应体

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/11d7c041-95cb-46f1-8e3c-68bb5e50855f/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_00_11_34.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB466YYTZN6CE%2F20260730%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260730T021310Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEML%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQDlBGVB1J%2F8EmMeywsZvwokkbB55zcoJtuKCgnf%2B4JwvgIhAPxWmjKY2h7HEMqzg8wtdwNLXtMArHXdx6NhNsl7pC9xKogECIv%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQABoMNjM3NDIzMTgzODA1IgyG3qfD9p6aC9En6h0q3AOLa3nqae4dVLS%2BtVEwMxyvmiKNRacyEnS1HUfQjw2TEhO9HA1bjHZR%2FXb5BIs2CpDZM%2BK7OL1mmsEDDOCTTCSC7MN20et6P7jkBi8dp06jYEFA0AEuTNRO9fW4zDWn6DTnJkM65lWdBKZvTC3rav2TuljfwefRxt%2FKg9nu6fcopVuoMVcw0Xi9mauP2%2FTelQFlhLHK0AL7oNr4lIWeZ5Dgm914c1OTREsW7%2BdrLnnVp8hdQ0aFPR4DDtQofgZ0EMv4JjltvblRiN7ICVSFB8M%2BuFvBRjAN53jSydKwZyavABtkubTzAJz1I1bEUgEyGfyKa64xOzAoLRqmiVpzTTniEDdlFD2T%2F95DkcEFgXCYcxOzd7qRRh1QDKGjpVyLOOGtwajDG%2F36%2Fr8BuadBtEpguE9i06tTZIcoIVhnQxc0G2U9D8x0pB5EsmcXD9JJvBoh9m5QjNggInscfpIn36gIbOZukHe7qftBOuc9aBLxmLowA72jw5v%2FaDS6Y0HXSIbKx9HL8%2BCG5L9iSR7vPm6WoDn2Ya6j0jwhrH97PN9xnU%2F65TeCiPFWwFDHGj3ODJcVvqBXhCgvrwN7gQx89SvNLxDrdRIpPDp7mLI1TY0YzB8LzonvTrI0HIvymTDn36rTBjqkAd8ArOib8%2Bu4Q20oSFCH3Gv9Hr8G8MO4c3TlDFaKjUe7oVeU17GnxT6bCSG90vNEz7qLJKvEvV3peFkv8NybG5vE4w3N1RKCehT9BArCi686Sxeutc7L%2FC8%2BRB4rWzXiqp1j2533O0IM8fnXeVgEKYAhnzn%2B1SEycaCxCcFXfFU0hs0pd31igj9MJG5n168bSqidlWl16mXxQbO18n5UdmWGTa6c&X-Amz-Signature=f55a5a7c8e221379c3b3c2651fd33b881b5a21459b6b27438479bb0389e7a163&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

### 常用 HTTP 方法（怎么用）

- **GET**：查询 / 获取资源  
  - 通常无请求体  
  - 参数多放在 URL Query  
  - 安全（safe）且幂等（idempotent）

- **POST**：创建资源 / 提交数据  
  - 常带请求体（JSON/Form）  
  - 一般不幂等（重复提交可能创建多条）

- **PUT**：完整替换资源  
  - 通常幂等（同一请求重复执行结果一致）  
  - 客户端需提供资源完整表示

- **PATCH**：部分更新资源  
  - 只传需要修改的字段  
  - 是否幂等取决于具体实现

- **DELETE**：删除资源  
  - 通常幂等（删不存在的资源也应返回一致结果或合适提示）

### HTTP 和 JSON 的关系（记住这句话）

> 1. **客户端发送 HTTP 请求**

> - 浏览器发送 HTTP 请求，请求中包含 **方法**、**地址**、**请求头**，以及可能存在的 **请求体**。

> 2. **服务器返回 HTTP 响应**

> - 服务器返回 HTTP 响应，响应中包含 **状态码**、**响应头** 和 **响应体**。

> - 响应体可以是 JSON。

> 3. **HTTP 是通信规则，JSON 是数据格式**

> - **HTTP** 负责传输和通信，**JSON** 负责数据的结构化表达。



### 常见状态码（看到就知道啥意思）

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/9af3f8c9-f55e-4af8-9468-e3f2762e3fb3/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_00_09_04.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB466YYTZN6CE%2F20260730%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260730T021310Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEML%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQDlBGVB1J%2F8EmMeywsZvwokkbB55zcoJtuKCgnf%2B4JwvgIhAPxWmjKY2h7HEMqzg8wtdwNLXtMArHXdx6NhNsl7pC9xKogECIv%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQABoMNjM3NDIzMTgzODA1IgyG3qfD9p6aC9En6h0q3AOLa3nqae4dVLS%2BtVEwMxyvmiKNRacyEnS1HUfQjw2TEhO9HA1bjHZR%2FXb5BIs2CpDZM%2BK7OL1mmsEDDOCTTCSC7MN20et6P7jkBi8dp06jYEFA0AEuTNRO9fW4zDWn6DTnJkM65lWdBKZvTC3rav2TuljfwefRxt%2FKg9nu6fcopVuoMVcw0Xi9mauP2%2FTelQFlhLHK0AL7oNr4lIWeZ5Dgm914c1OTREsW7%2BdrLnnVp8hdQ0aFPR4DDtQofgZ0EMv4JjltvblRiN7ICVSFB8M%2BuFvBRjAN53jSydKwZyavABtkubTzAJz1I1bEUgEyGfyKa64xOzAoLRqmiVpzTTniEDdlFD2T%2F95DkcEFgXCYcxOzd7qRRh1QDKGjpVyLOOGtwajDG%2F36%2Fr8BuadBtEpguE9i06tTZIcoIVhnQxc0G2U9D8x0pB5EsmcXD9JJvBoh9m5QjNggInscfpIn36gIbOZukHe7qftBOuc9aBLxmLowA72jw5v%2FaDS6Y0HXSIbKx9HL8%2BCG5L9iSR7vPm6WoDn2Ya6j0jwhrH97PN9xnU%2F65TeCiPFWwFDHGj3ODJcVvqBXhCgvrwN7gQx89SvNLxDrdRIpPDp7mLI1TY0YzB8LzonvTrI0HIvymTDn36rTBjqkAd8ArOib8%2Bu4Q20oSFCH3Gv9Hr8G8MO4c3TlDFaKjUe7oVeU17GnxT6bCSG90vNEz7qLJKvEvV3peFkv8NybG5vE4w3N1RKCehT9BArCi686Sxeutc7L%2FC8%2BRB4rWzXiqp1j2533O0IM8fnXeVgEKYAhnzn%2B1SEycaCxCcFXfFU0hs0pd31igj9MJG5n168bSqidlWl16mXxQbO18n5UdmWGTa6c&X-Amz-Signature=03883b4e31ec028e615526418f51ddb5bb719538b95b33661b3e4dcf004a8671&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

## HTTP 在 Gin 中的体现

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/24d293b6-5e06-4a8d-b324-da3acb9f2ee4/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_21_27_27.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB466YYTZN6CE%2F20260730%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260730T021310Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEML%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQDlBGVB1J%2F8EmMeywsZvwokkbB55zcoJtuKCgnf%2B4JwvgIhAPxWmjKY2h7HEMqzg8wtdwNLXtMArHXdx6NhNsl7pC9xKogECIv%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQABoMNjM3NDIzMTgzODA1IgyG3qfD9p6aC9En6h0q3AOLa3nqae4dVLS%2BtVEwMxyvmiKNRacyEnS1HUfQjw2TEhO9HA1bjHZR%2FXb5BIs2CpDZM%2BK7OL1mmsEDDOCTTCSC7MN20et6P7jkBi8dp06jYEFA0AEuTNRO9fW4zDWn6DTnJkM65lWdBKZvTC3rav2TuljfwefRxt%2FKg9nu6fcopVuoMVcw0Xi9mauP2%2FTelQFlhLHK0AL7oNr4lIWeZ5Dgm914c1OTREsW7%2BdrLnnVp8hdQ0aFPR4DDtQofgZ0EMv4JjltvblRiN7ICVSFB8M%2BuFvBRjAN53jSydKwZyavABtkubTzAJz1I1bEUgEyGfyKa64xOzAoLRqmiVpzTTniEDdlFD2T%2F95DkcEFgXCYcxOzd7qRRh1QDKGjpVyLOOGtwajDG%2F36%2Fr8BuadBtEpguE9i06tTZIcoIVhnQxc0G2U9D8x0pB5EsmcXD9JJvBoh9m5QjNggInscfpIn36gIbOZukHe7qftBOuc9aBLxmLowA72jw5v%2FaDS6Y0HXSIbKx9HL8%2BCG5L9iSR7vPm6WoDn2Ya6j0jwhrH97PN9xnU%2F65TeCiPFWwFDHGj3ODJcVvqBXhCgvrwN7gQx89SvNLxDrdRIpPDp7mLI1TY0YzB8LzonvTrI0HIvymTDn36rTBjqkAd8ArOib8%2Bu4Q20oSFCH3Gv9Hr8G8MO4c3TlDFaKjUe7oVeU17GnxT6bCSG90vNEz7qLJKvEvV3peFkv8NybG5vE4w3N1RKCehT9BArCi686Sxeutc7L%2FC8%2BRB4rWzXiqp1j2533O0IM8fnXeVgEKYAhnzn%2B1SEycaCxCcFXfFU0hs0pd31igj9MJG5n168bSqidlWl16mXxQbO18n5UdmWGTa6c&X-Amz-Signature=e17911fd2986f75343d063543ba244ed02f7c536ca4fcba655728583ba351f1b&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

**客户端数据来源（4 类）**

- URL 路径参数（Path Param）
- 查询参数（Query Param）
- 请求头（Header）
- 请求体（Body）
Gin 通过对应 API 读取这些数据，并常用 `c.JSON()` 返回 JSON 响应。

---

**1）路径参数（Path Param）：****`c.Param()`**  

路径中的动态值（例如 `:id`）：

```plain text
GET /users/15
```

```go
r.GET("/users/:id", getUser)

id := c.Param("id") // string
```

---

**2）查询参数（Query Param）：****`c.Query()`**  

位于 URL 的 `?` 后面：

```plain text
GET /users?keyword=nova
```

```go
keyword := c.Query("keyword")
```

注意区分：

```plain text
c.Query()  → 读取 URL 参数
DB.Query() → 查询数据库
```

---

**3）JSON 请求体（Body）：****`c.ShouldBindJSON()`**

客户端发送（JSON）：

```json
{
  "name": "Nova",
  "age": 20
}
```

Gin 解析到结构体：

```go
var req CreateUserRequest

if err := c.ShouldBindJSON(&req); err != nil {
    return
}
```

作用（一句话）：

```plain text
读取请求体 → 解析 JSON → 写入结构体
```

---

**4）请求头（Header）：****`c.GetHeader()`**

请求头是客户端携带的附加信息（数据格式、身份凭证、请求来源等）：

```go
value := c.GetHeader("Header-Name")
```

常见 Header：

- **Content-Type**：说明「请求体」的格式
```plain text
Content-Type: application/json
```


- **Authorization**：携带身份认证信息
```plain text
Authorization: Bearer token123
```

拆开理解：

```plain text
Authorization → 请求头名称
Bearer        → 认证方式
token123      → Token
```

Gin 获取完整内容：

```go
authHeader := c.GetHeader("Authorization")
// "Bearer token123"
```

JWT 通常通过这个请求头发送给后端。


- **Accept**：说明客户端希望服务器返回什么格式
```plain text
Accept: application/json
```

```plain text
Content-Type → 我发送的数据格式
Accept       → 我希望收到的数据格式
```


- **Origin**：说明请求来自哪个网站，常用于跨域判断  
- **User-Agent**：说明请求来自浏览器、Postman、手机应用等哪种客户端
---

**返回响应：****`c.JSON()`**

```go
c.JSON(http.StatusOK, gin.H{
    "message": "success",
    "data":    user,
})
```

作用：

```plain text
设置状态码 → 转换为 JSON → 写入响应体
```

---

**最终速记**

```plain text
路径中的值   → c.Param()
问号后的值   → c.Query()
请求头信息   → c.GetHeader()
JSON 请求体  → c.ShouldBindJSON()
返回 JSON    → c.JSON()
```
