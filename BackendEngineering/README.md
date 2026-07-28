# 后端

## 目录

---

## 一次 Web 请求的完整流程（请求 → 响应）

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/e07a5a4d-a509-40ba-a41e-372489b69a56/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8827%E6%97%A5_15_35_37.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB4665OZJKD7N%2F20260728%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260728T022657Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEI%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJGMEQCIHllRMk5V8stoRpl8BB95vHM1vuaf7hzZUt1FPc9r2WhAiAkzjoSPqyU%2BhX5HtJTWytNyUr81JY6bmTM4EZ8u1gvaCr%2FAwhYEAAaDDYzNzQyMzE4MzgwNSIM0ImLNA%2B%2Bpu2dQgXuKtwDNX7D3yPZxfCBsdNQdDCNn5ooHXAU6UTD%2BEwXk2sWkp9bMdxz5oqasa%2BUVaofrc3tYkE9j8rHFPhiCcuuna%2FtiHg8WxbuLsCpGb2aMIqxQIFRVF8xakET26proWawAiOIOMRwuTcdbqWAtESybVUtjd8lVeHGrIIW52hzFZ8DulA1pjSvyQdSK7CYRblAmfGMIZmtCXEsfCuoy%2BxKEyH7mFSKXnX2hGQymAK9bIzJxeo5WWfC6uPSd1r1HXUZCWgGd4xqe7p1mrV1IKiUW6%2BfQzutYpI5lkyjQwBRK7GP0FszXQBMeceWdOGhrWb2GFfbkajDihzodSQccPXIFao3b72YCY13M5lHr8Hpiqab5BU4Q7Xfb0iwF0OGsLc2b4%2BVTmYFLsianHKUPPkITX2Gyzgw5v5CU9yRnSZDrBE%2FryCsdihktGD%2BFDCA7XiRKem%2FAe6HdU0Jo7fPo2d%2FZmMEYQYLL0f2S3Lkms5ItPpXEXmdlW0v634ROl9NJ6eLK%2BYp7jb3pfx3EOaIUy8Awd5E4gP4qjdyWdZVDYRKvvVv4zhUQqG1NEHLSwGndS1w3gZ%2F7mwqJTby18lgXTtvmqlldHS%2Fho02ZKAJNvstcUHx0QyhvGseUpKnI5TWTrYwlMWf0wY6pgG%2BTxyS%2BLVLvxMBcmTVuNGpTit6QuDBaWtcL3yBMR5IePakzKBAZ9qUC4O4mFRYleaj58w4l4ugtywQPY1kLrpBmG8cUkFx5FpOghuMOFZDHEg5s0gCxyx2g3BMji%2F%2FRIcVrOuVLiP3ne3dyqrSXcHC3cjoCG%2BLwdEog86IXt5L%2FvegpMq0L4T%2FskhuNdgzkbD4hs535Rnp3lBF6MGJwCW5WK9xAIYN&X-Amz-Signature=1439f08cdb93d6e0d2d4c0e9c8d893db7013bf7a00b0267dcb2b82f68d71ee2f&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

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

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/11d7c041-95cb-46f1-8e3c-68bb5e50855f/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_00_11_34.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB4665OZJKD7N%2F20260728%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260728T022657Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEI%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJGMEQCIHllRMk5V8stoRpl8BB95vHM1vuaf7hzZUt1FPc9r2WhAiAkzjoSPqyU%2BhX5HtJTWytNyUr81JY6bmTM4EZ8u1gvaCr%2FAwhYEAAaDDYzNzQyMzE4MzgwNSIM0ImLNA%2B%2Bpu2dQgXuKtwDNX7D3yPZxfCBsdNQdDCNn5ooHXAU6UTD%2BEwXk2sWkp9bMdxz5oqasa%2BUVaofrc3tYkE9j8rHFPhiCcuuna%2FtiHg8WxbuLsCpGb2aMIqxQIFRVF8xakET26proWawAiOIOMRwuTcdbqWAtESybVUtjd8lVeHGrIIW52hzFZ8DulA1pjSvyQdSK7CYRblAmfGMIZmtCXEsfCuoy%2BxKEyH7mFSKXnX2hGQymAK9bIzJxeo5WWfC6uPSd1r1HXUZCWgGd4xqe7p1mrV1IKiUW6%2BfQzutYpI5lkyjQwBRK7GP0FszXQBMeceWdOGhrWb2GFfbkajDihzodSQccPXIFao3b72YCY13M5lHr8Hpiqab5BU4Q7Xfb0iwF0OGsLc2b4%2BVTmYFLsianHKUPPkITX2Gyzgw5v5CU9yRnSZDrBE%2FryCsdihktGD%2BFDCA7XiRKem%2FAe6HdU0Jo7fPo2d%2FZmMEYQYLL0f2S3Lkms5ItPpXEXmdlW0v634ROl9NJ6eLK%2BYp7jb3pfx3EOaIUy8Awd5E4gP4qjdyWdZVDYRKvvVv4zhUQqG1NEHLSwGndS1w3gZ%2F7mwqJTby18lgXTtvmqlldHS%2Fho02ZKAJNvstcUHx0QyhvGseUpKnI5TWTrYwlMWf0wY6pgG%2BTxyS%2BLVLvxMBcmTVuNGpTit6QuDBaWtcL3yBMR5IePakzKBAZ9qUC4O4mFRYleaj58w4l4ugtywQPY1kLrpBmG8cUkFx5FpOghuMOFZDHEg5s0gCxyx2g3BMji%2F%2FRIcVrOuVLiP3ne3dyqrSXcHC3cjoCG%2BLwdEog86IXt5L%2FvegpMq0L4T%2FskhuNdgzkbD4hs535Rnp3lBF6MGJwCW5WK9xAIYN&X-Amz-Signature=90656df80dd40ae8c089cccb47154cb644594f0e1abfa787fdaa216ea795e944&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

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

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/9af3f8c9-f55e-4af8-9468-e3f2762e3fb3/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_00_09_04.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB4665OZJKD7N%2F20260728%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260728T022657Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEI%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJGMEQCIHllRMk5V8stoRpl8BB95vHM1vuaf7hzZUt1FPc9r2WhAiAkzjoSPqyU%2BhX5HtJTWytNyUr81JY6bmTM4EZ8u1gvaCr%2FAwhYEAAaDDYzNzQyMzE4MzgwNSIM0ImLNA%2B%2Bpu2dQgXuKtwDNX7D3yPZxfCBsdNQdDCNn5ooHXAU6UTD%2BEwXk2sWkp9bMdxz5oqasa%2BUVaofrc3tYkE9j8rHFPhiCcuuna%2FtiHg8WxbuLsCpGb2aMIqxQIFRVF8xakET26proWawAiOIOMRwuTcdbqWAtESybVUtjd8lVeHGrIIW52hzFZ8DulA1pjSvyQdSK7CYRblAmfGMIZmtCXEsfCuoy%2BxKEyH7mFSKXnX2hGQymAK9bIzJxeo5WWfC6uPSd1r1HXUZCWgGd4xqe7p1mrV1IKiUW6%2BfQzutYpI5lkyjQwBRK7GP0FszXQBMeceWdOGhrWb2GFfbkajDihzodSQccPXIFao3b72YCY13M5lHr8Hpiqab5BU4Q7Xfb0iwF0OGsLc2b4%2BVTmYFLsianHKUPPkITX2Gyzgw5v5CU9yRnSZDrBE%2FryCsdihktGD%2BFDCA7XiRKem%2FAe6HdU0Jo7fPo2d%2FZmMEYQYLL0f2S3Lkms5ItPpXEXmdlW0v634ROl9NJ6eLK%2BYp7jb3pfx3EOaIUy8Awd5E4gP4qjdyWdZVDYRKvvVv4zhUQqG1NEHLSwGndS1w3gZ%2F7mwqJTby18lgXTtvmqlldHS%2Fho02ZKAJNvstcUHx0QyhvGseUpKnI5TWTrYwlMWf0wY6pgG%2BTxyS%2BLVLvxMBcmTVuNGpTit6QuDBaWtcL3yBMR5IePakzKBAZ9qUC4O4mFRYleaj58w4l4ugtywQPY1kLrpBmG8cUkFx5FpOghuMOFZDHEg5s0gCxyx2g3BMji%2F%2FRIcVrOuVLiP3ne3dyqrSXcHC3cjoCG%2BLwdEog86IXt5L%2FvegpMq0L4T%2FskhuNdgzkbD4hs535Rnp3lBF6MGJwCW5WK9xAIYN&X-Amz-Signature=123bdd21e8e11377a9a254f5e690adf5374e4b8d987f6212457d9273aef85f8d&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)
