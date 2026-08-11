# 后端

## 目录

---

## 一次 Web 请求的完整流程（请求 → 响应）

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/e07a5a4d-a509-40ba-a41e-372489b69a56/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8827%E6%97%A5_15_35_37.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB4663XTQ4NWT%2F20260811%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260811T013834Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEOH%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQCVMEDKkL3aS9TqVO7A83w6avsJSN3shQe1FjQUw1ssrAIhANWI1XOQwU84J4hLh2i71k%2BXMT83nTzMHgVL%2FxdV62LiKogECKr%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQABoMNjM3NDIzMTgzODA1IgxJ70G9wac8sstkwJQq3ANhWblqLRIerGoOOO0H8uTYY2AOC9i2PQV%2FgZrh5bnAcctUFTtnTVSyJ592zaoAphBN6maNaZzQzUUz03UjKmsQJp58acrWKy58enecKl1FJRjhGfogC4t3m0H9Y6uNGCL%2F27zEky0dIdn%2BRjpIe%2BhpFJ3KCvt%2F4jYO6CKTI2yuAOdYqKENb%2FhWMzgRyEsAjM%2BWfAcylWWTLEyIelfS1TVHH2VroDMpZ5XLfTPIE%2Fs%2FAVTDm8yBxKUoWNgw8WKnladRswhH%2BHOIIuQZs0q%2F7urUwtAu7RRn507PNN6PQvxrIPNp5XCfilAIq9bNv2ia0xEhkSMArO5X%2BHR7JEkBasKMSC4cn8Uu6szb8H1LjQlh7UtGAhSzdPtIMDfRT1m8Vx2HLs0RydaKfuN6zD090XxFfge%2BVMb6SzLIw3CdwFpFNBY7Sjrz4VrbOf1spON6cXA6%2Fw3FrcNM98Ln83o5IZUezbEcy4cROu7hamWWg0VFdOoMs4BNW7ysHlnxSN16m2jYaxYSMDz3h%2F7on32hAN%2BZYJjrLg%2BgNVMY7MCnPiHO9Be0FHGCvTEzC0db%2F48CoVhxBUPEfstJnsOc%2BdhSq1LaZOSAWdMgS4aJONKzSadaCwb1alO1Ph1v1wSjbTDs2unTBjqkAYKdE5xcyN1f7iDZ7aHGM4ElOp5GfBGTYEmDuCWRO2QnTgp1R3svYKHUwXT7T0ulOMtzaq5eCuFVmE8ULqVJfcVe%2FeB%2FB%2BNylGg1uEwk9o3BtoVPWA9XSRnv2W46iCMap04MVd60HY4pUA6ICNSEBe4EGqtpkhLmEwXrH0wwzdP2IWC4aZguVFVpFsg0lNg1eSJcL1BWUGnbTsXC7qIJV44E9iWM&X-Amz-Signature=b95d294fe42ed36c31c3d3a0f53edfcd0b2a358506b1b55e2f808cf13d73f790&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

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

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/11d7c041-95cb-46f1-8e3c-68bb5e50855f/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_00_11_34.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB4663XTQ4NWT%2F20260811%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260811T013834Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEOH%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQCVMEDKkL3aS9TqVO7A83w6avsJSN3shQe1FjQUw1ssrAIhANWI1XOQwU84J4hLh2i71k%2BXMT83nTzMHgVL%2FxdV62LiKogECKr%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQABoMNjM3NDIzMTgzODA1IgxJ70G9wac8sstkwJQq3ANhWblqLRIerGoOOO0H8uTYY2AOC9i2PQV%2FgZrh5bnAcctUFTtnTVSyJ592zaoAphBN6maNaZzQzUUz03UjKmsQJp58acrWKy58enecKl1FJRjhGfogC4t3m0H9Y6uNGCL%2F27zEky0dIdn%2BRjpIe%2BhpFJ3KCvt%2F4jYO6CKTI2yuAOdYqKENb%2FhWMzgRyEsAjM%2BWfAcylWWTLEyIelfS1TVHH2VroDMpZ5XLfTPIE%2Fs%2FAVTDm8yBxKUoWNgw8WKnladRswhH%2BHOIIuQZs0q%2F7urUwtAu7RRn507PNN6PQvxrIPNp5XCfilAIq9bNv2ia0xEhkSMArO5X%2BHR7JEkBasKMSC4cn8Uu6szb8H1LjQlh7UtGAhSzdPtIMDfRT1m8Vx2HLs0RydaKfuN6zD090XxFfge%2BVMb6SzLIw3CdwFpFNBY7Sjrz4VrbOf1spON6cXA6%2Fw3FrcNM98Ln83o5IZUezbEcy4cROu7hamWWg0VFdOoMs4BNW7ysHlnxSN16m2jYaxYSMDz3h%2F7on32hAN%2BZYJjrLg%2BgNVMY7MCnPiHO9Be0FHGCvTEzC0db%2F48CoVhxBUPEfstJnsOc%2BdhSq1LaZOSAWdMgS4aJONKzSadaCwb1alO1Ph1v1wSjbTDs2unTBjqkAYKdE5xcyN1f7iDZ7aHGM4ElOp5GfBGTYEmDuCWRO2QnTgp1R3svYKHUwXT7T0ulOMtzaq5eCuFVmE8ULqVJfcVe%2FeB%2FB%2BNylGg1uEwk9o3BtoVPWA9XSRnv2W46iCMap04MVd60HY4pUA6ICNSEBe4EGqtpkhLmEwXrH0wwzdP2IWC4aZguVFVpFsg0lNg1eSJcL1BWUGnbTsXC7qIJV44E9iWM&X-Amz-Signature=d76efac90cf8464342425c155698fcb54370ae4b2b8fc525cf9bd9948be2ec1d&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

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

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/9af3f8c9-f55e-4af8-9468-e3f2762e3fb3/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_00_09_04.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB4663XTQ4NWT%2F20260811%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260811T013834Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEOH%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQCVMEDKkL3aS9TqVO7A83w6avsJSN3shQe1FjQUw1ssrAIhANWI1XOQwU84J4hLh2i71k%2BXMT83nTzMHgVL%2FxdV62LiKogECKr%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQABoMNjM3NDIzMTgzODA1IgxJ70G9wac8sstkwJQq3ANhWblqLRIerGoOOO0H8uTYY2AOC9i2PQV%2FgZrh5bnAcctUFTtnTVSyJ592zaoAphBN6maNaZzQzUUz03UjKmsQJp58acrWKy58enecKl1FJRjhGfogC4t3m0H9Y6uNGCL%2F27zEky0dIdn%2BRjpIe%2BhpFJ3KCvt%2F4jYO6CKTI2yuAOdYqKENb%2FhWMzgRyEsAjM%2BWfAcylWWTLEyIelfS1TVHH2VroDMpZ5XLfTPIE%2Fs%2FAVTDm8yBxKUoWNgw8WKnladRswhH%2BHOIIuQZs0q%2F7urUwtAu7RRn507PNN6PQvxrIPNp5XCfilAIq9bNv2ia0xEhkSMArO5X%2BHR7JEkBasKMSC4cn8Uu6szb8H1LjQlh7UtGAhSzdPtIMDfRT1m8Vx2HLs0RydaKfuN6zD090XxFfge%2BVMb6SzLIw3CdwFpFNBY7Sjrz4VrbOf1spON6cXA6%2Fw3FrcNM98Ln83o5IZUezbEcy4cROu7hamWWg0VFdOoMs4BNW7ysHlnxSN16m2jYaxYSMDz3h%2F7on32hAN%2BZYJjrLg%2BgNVMY7MCnPiHO9Be0FHGCvTEzC0db%2F48CoVhxBUPEfstJnsOc%2BdhSq1LaZOSAWdMgS4aJONKzSadaCwb1alO1Ph1v1wSjbTDs2unTBjqkAYKdE5xcyN1f7iDZ7aHGM4ElOp5GfBGTYEmDuCWRO2QnTgp1R3svYKHUwXT7T0ulOMtzaq5eCuFVmE8ULqVJfcVe%2FeB%2FB%2BNylGg1uEwk9o3BtoVPWA9XSRnv2W46iCMap04MVd60HY4pUA6ICNSEBe4EGqtpkhLmEwXrH0wwzdP2IWC4aZguVFVpFsg0lNg1eSJcL1BWUGnbTsXC7qIJV44E9iWM&X-Amz-Signature=9ac5e62c87a107e6a09d194fac850e63f767c31c4ee86a49f687aadb936a6dd7&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

## HTTP 在 Gin 中的体现

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/24d293b6-5e06-4a8d-b324-da3acb9f2ee4/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_21_27_27.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB4663XTQ4NWT%2F20260811%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260811T013834Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEOH%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQCVMEDKkL3aS9TqVO7A83w6avsJSN3shQe1FjQUw1ssrAIhANWI1XOQwU84J4hLh2i71k%2BXMT83nTzMHgVL%2FxdV62LiKogECKr%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQABoMNjM3NDIzMTgzODA1IgxJ70G9wac8sstkwJQq3ANhWblqLRIerGoOOO0H8uTYY2AOC9i2PQV%2FgZrh5bnAcctUFTtnTVSyJ592zaoAphBN6maNaZzQzUUz03UjKmsQJp58acrWKy58enecKl1FJRjhGfogC4t3m0H9Y6uNGCL%2F27zEky0dIdn%2BRjpIe%2BhpFJ3KCvt%2F4jYO6CKTI2yuAOdYqKENb%2FhWMzgRyEsAjM%2BWfAcylWWTLEyIelfS1TVHH2VroDMpZ5XLfTPIE%2Fs%2FAVTDm8yBxKUoWNgw8WKnladRswhH%2BHOIIuQZs0q%2F7urUwtAu7RRn507PNN6PQvxrIPNp5XCfilAIq9bNv2ia0xEhkSMArO5X%2BHR7JEkBasKMSC4cn8Uu6szb8H1LjQlh7UtGAhSzdPtIMDfRT1m8Vx2HLs0RydaKfuN6zD090XxFfge%2BVMb6SzLIw3CdwFpFNBY7Sjrz4VrbOf1spON6cXA6%2Fw3FrcNM98Ln83o5IZUezbEcy4cROu7hamWWg0VFdOoMs4BNW7ysHlnxSN16m2jYaxYSMDz3h%2F7on32hAN%2BZYJjrLg%2BgNVMY7MCnPiHO9Be0FHGCvTEzC0db%2F48CoVhxBUPEfstJnsOc%2BdhSq1LaZOSAWdMgS4aJONKzSadaCwb1alO1Ph1v1wSjbTDs2unTBjqkAYKdE5xcyN1f7iDZ7aHGM4ElOp5GfBGTYEmDuCWRO2QnTgp1R3svYKHUwXT7T0ulOMtzaq5eCuFVmE8ULqVJfcVe%2FeB%2FB%2BNylGg1uEwk9o3BtoVPWA9XSRnv2W46iCMap04MVd60HY4pUA6ICNSEBe4EGqtpkhLmEwXrH0wwzdP2IWC4aZguVFVpFsg0lNg1eSJcL1BWUGnbTsXC7qIJV44E9iWM&X-Amz-Signature=9b9dc60511a8c3da157867ff30721b4907b77cf700dc025d35641ab3396a99e4&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

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



## TCP: 可靠的数据传输协议

特点是:面向连接(
不仅仅是建立连接时要确认，**传输过程中的每一个数据包，都需要对方回复一个“已收到”（ACK）**。发一件，确认一件，不见兔子不撒鹰

)

自动重传(**谁是发送方，谁就负责重发。** 不管是客户端发给服务端，还是服务端发给客户端，只要发送方等了一段时间没听到“已收到”的回复，就会觉得“肯定半路丢了”，然后自动重新发一次。

)

保证顺序(
乱序的原因，主要是因为**网络太复杂了**。这就好比你寄了三个快递，有的包裹走了高速，有的包裹绕了弯路，导致后寄的反而先到了。TCP 接收端会在内部把它们按照原来的 1、2、3 编号重新排好队，再交给你的程序。

)



三次握手(建立连接):

### 专业说法（术语版）

TCP 三次握手的核心目的是同步双方的序列号，并确认双方的全双工（收发）通信能力已准备就绪：

1. **第一次握手：** 客户端发送 **`SYN`** 报文给服务端，进入同步已发送状态。
1. **第二次握手：** 服务端收到后，回复 **`SYN + ACK`** 报文给客户端，进入同步收到状态。
1. **第三次握手：** 客户端收到后，回复 **`ACK`** 报文给服务端，双方进入连接已建立状态。
### 🗣️ 通俗理解（你的大白话版）

核心逻辑就是双方互相测试“能不能听见”和“能不能说话”：

1. **第一遍（客户端）：** “你能收到没？” （发 `SYN`）
1. **第二遍（服务端）：** “我收到了！那你能收到我说话吗？” （发 `SYN` + `ACK`，证明自己**能收也能发**）
1. **第三遍（客户端）：** “我也能收到！” （发 `ACK`，证明自己也**能收**，双向通道完全打通）
四次挥手(安全断开连接)

### 专业说法（术语版）

1. **第一次挥手：** 客户端发送 `FIN` 报文（表示我没数据要发了，请求关闭）。
1. **第二次挥手：** 服务端发送 `ACK` 报文（表示收到你的请求，但我可能还有数据没发完，进入“半关闭”状态）。
1. **第三次挥手：** 服务端发送 `FIN` 报文（表示我的数据也全发完了，可以正式关闭）。
1. **第四次挥手：** 客户端发送 `ACK` 报文（表示收到。服务端收到后立刻关闭；客户端进入 `TIME_WAIT` 等待一小段时间后，也彻底关闭）。
### 🗣️ 通俗理解（大白话版）

1. **客户端：** “我讲完了，准备挂电话了。”
1. **服务端：** “收到，**但你先别挂**，我这还有两句话没交代完。”
1. **服务端（过了一会）：** “好了，我也全部交代完了，挂了吧。”
1. **客户端：** “好的，拜拜！”（并在原地稍微等一会，确认对方没再重喊自己，然后彻底走人）。
> **💡 核心补充：** 为什么要四次？因为第二步（收到）和第三步（我也结束了）中间通常**有时间差**，得等服务端干完手头的活儿。如果服务端刚好也没活儿了，这两步就会合并，变成“三次挥手”。
