# 后端

## 目录

---

## 一次 Web 请求的完整流程（请求 → 响应）

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/e07a5a4d-a509-40ba-a41e-372489b69a56/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8827%E6%97%A5_15_35_37.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB466ZU4UJN5Q%2F20260728%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260728T012224Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEI%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJHMEUCIQDbEqSUyl7ThbvVItpjF2KxsTpSQ2WI70HujvqDOr7A4AIgCLbe6ra6t7KXJsXMDeRQnqkqZySd2YI90zurvwOBW3Uq%2FwMIWBAAGgw2Mzc0MjMxODM4MDUiDKH27DKt6lOYcIHVTCrcA0JHY0TIlj%2Bz5WwLNHIwUYYepGTej49F8TVWOoceBLZ3EY5cB5HyrNgENJEn00oxp3ESO9HTfm0nMjECFGyON%2BYCBY4KpsKZgBx%2BwJJgACxl22hnkizumnUeOlrqK2DiVdt9T7RsGOT5hDZkOtzCDKzgnib1%2Bt4KaKG6tZ%2BrPJMfeUwUy2VMZ3pz8qfs%2BVyd7TEm2A5G4q%2F72CmZUWMqpS0Ii5u9WTPC2UVnABQ3n%2BqcdHFY5yxSLd7alFbtlpKt%2BzEeLxF%2FjRcySX6RShVag%2FVT3v2rrb%2FqbPaceTPO0zLII1GzSc5ha6LVU6lwhs1KZqTZvXvmz8OEtb3QiKDkcAoXKd89tudNcTf%2F0u0bRlPXQycyko3%2BApTnm602UNBok1SarsjS74C%2BrfwWF2Cj2twUGNzmlcgDiq%2F9sczTh30bhVHiOHJNfXUIaL9lNllPJnC4ROL7CJDBtAGhxs6azew2DwcrS7PIVzD3LorBO7fJ7z2qn6sXp6Aj3dNkJH9M4%2BsnY%2FacKPKk9h74Q01RBI6SpioqJokvvB4HQACAlHCEJEvs4Sv0jUeDIOzIkwc3%2FET6sMG0ddUvjaJ6t434xhVrvhoZeUf2L%2BXWi8rFSAKp1F2lF%2Bs7w1mEbAOdMOjEn9MGOqUBm0jV%2FXlwGoihvTGwPAl%2B3Yd%2BMgJXoYJIXNQsmAWKgmjKeCK2bRDb1y6dDTGM4C8Yz7CqW6GI4f2RbRD2lANQKuJTKxsLNzo022IS%2B2k3Dg5MjAdAmrlHAq24Q1SbfwBIvf4aneBxOF%2BfAkp82AdXglZr9kzgKo5EMmR%2FTz3oJPk%2FEowOo8aGVL3%2FbGGsDMSZjamA3SamPN%2FAXV2zW0bRLQuO5gQM&X-Amz-Signature=b8ded0169e0fa9aae45c27353dcde118a98ccec4b31bdd8b11322238b9a6a959&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

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

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/11d7c041-95cb-46f1-8e3c-68bb5e50855f/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_00_11_34.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB466ZU4UJN5Q%2F20260728%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260728T012224Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEI%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJHMEUCIQDbEqSUyl7ThbvVItpjF2KxsTpSQ2WI70HujvqDOr7A4AIgCLbe6ra6t7KXJsXMDeRQnqkqZySd2YI90zurvwOBW3Uq%2FwMIWBAAGgw2Mzc0MjMxODM4MDUiDKH27DKt6lOYcIHVTCrcA0JHY0TIlj%2Bz5WwLNHIwUYYepGTej49F8TVWOoceBLZ3EY5cB5HyrNgENJEn00oxp3ESO9HTfm0nMjECFGyON%2BYCBY4KpsKZgBx%2BwJJgACxl22hnkizumnUeOlrqK2DiVdt9T7RsGOT5hDZkOtzCDKzgnib1%2Bt4KaKG6tZ%2BrPJMfeUwUy2VMZ3pz8qfs%2BVyd7TEm2A5G4q%2F72CmZUWMqpS0Ii5u9WTPC2UVnABQ3n%2BqcdHFY5yxSLd7alFbtlpKt%2BzEeLxF%2FjRcySX6RShVag%2FVT3v2rrb%2FqbPaceTPO0zLII1GzSc5ha6LVU6lwhs1KZqTZvXvmz8OEtb3QiKDkcAoXKd89tudNcTf%2F0u0bRlPXQycyko3%2BApTnm602UNBok1SarsjS74C%2BrfwWF2Cj2twUGNzmlcgDiq%2F9sczTh30bhVHiOHJNfXUIaL9lNllPJnC4ROL7CJDBtAGhxs6azew2DwcrS7PIVzD3LorBO7fJ7z2qn6sXp6Aj3dNkJH9M4%2BsnY%2FacKPKk9h74Q01RBI6SpioqJokvvB4HQACAlHCEJEvs4Sv0jUeDIOzIkwc3%2FET6sMG0ddUvjaJ6t434xhVrvhoZeUf2L%2BXWi8rFSAKp1F2lF%2Bs7w1mEbAOdMOjEn9MGOqUBm0jV%2FXlwGoihvTGwPAl%2B3Yd%2BMgJXoYJIXNQsmAWKgmjKeCK2bRDb1y6dDTGM4C8Yz7CqW6GI4f2RbRD2lANQKuJTKxsLNzo022IS%2B2k3Dg5MjAdAmrlHAq24Q1SbfwBIvf4aneBxOF%2BfAkp82AdXglZr9kzgKo5EMmR%2FTz3oJPk%2FEowOo8aGVL3%2FbGGsDMSZjamA3SamPN%2FAXV2zW0bRLQuO5gQM&X-Amz-Signature=42a0760d58b3bd4c723693377a138b2bb0d2fda42e70afd8906451f423e7f609&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)

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

![](https://prod-files-secure.s3.us-west-2.amazonaws.com/c426e1d9-0689-813f-b6fb-0003a890664c/9af3f8c9-f55e-4af8-9468-e3f2762e3fb3/ChatGPT_Image_2026%E5%B9%B47%E6%9C%8828%E6%97%A5_00_09_04.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=ASIAZI2LB466ZU4UJN5Q%2F20260728%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20260728T012224Z&X-Amz-Expires=3600&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEI%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJHMEUCIQDbEqSUyl7ThbvVItpjF2KxsTpSQ2WI70HujvqDOr7A4AIgCLbe6ra6t7KXJsXMDeRQnqkqZySd2YI90zurvwOBW3Uq%2FwMIWBAAGgw2Mzc0MjMxODM4MDUiDKH27DKt6lOYcIHVTCrcA0JHY0TIlj%2Bz5WwLNHIwUYYepGTej49F8TVWOoceBLZ3EY5cB5HyrNgENJEn00oxp3ESO9HTfm0nMjECFGyON%2BYCBY4KpsKZgBx%2BwJJgACxl22hnkizumnUeOlrqK2DiVdt9T7RsGOT5hDZkOtzCDKzgnib1%2Bt4KaKG6tZ%2BrPJMfeUwUy2VMZ3pz8qfs%2BVyd7TEm2A5G4q%2F72CmZUWMqpS0Ii5u9WTPC2UVnABQ3n%2BqcdHFY5yxSLd7alFbtlpKt%2BzEeLxF%2FjRcySX6RShVag%2FVT3v2rrb%2FqbPaceTPO0zLII1GzSc5ha6LVU6lwhs1KZqTZvXvmz8OEtb3QiKDkcAoXKd89tudNcTf%2F0u0bRlPXQycyko3%2BApTnm602UNBok1SarsjS74C%2BrfwWF2Cj2twUGNzmlcgDiq%2F9sczTh30bhVHiOHJNfXUIaL9lNllPJnC4ROL7CJDBtAGhxs6azew2DwcrS7PIVzD3LorBO7fJ7z2qn6sXp6Aj3dNkJH9M4%2BsnY%2FacKPKk9h74Q01RBI6SpioqJokvvB4HQACAlHCEJEvs4Sv0jUeDIOzIkwc3%2FET6sMG0ddUvjaJ6t434xhVrvhoZeUf2L%2BXWi8rFSAKp1F2lF%2Bs7w1mEbAOdMOjEn9MGOqUBm0jV%2FXlwGoihvTGwPAl%2B3Yd%2BMgJXoYJIXNQsmAWKgmjKeCK2bRDb1y6dDTGM4C8Yz7CqW6GI4f2RbRD2lANQKuJTKxsLNzo022IS%2B2k3Dg5MjAdAmrlHAq24Q1SbfwBIvf4aneBxOF%2BfAkp82AdXglZr9kzgKo5EMmR%2FTz3oJPk%2FEowOo8aGVL3%2FbGGsDMSZjamA3SamPN%2FAXV2zW0bRLQuO5gQM&X-Amz-Signature=8453c61a908c099082b6a5fac3837c2412a1c1c8866c0bcff38cc2c0ff5537ca&X-Amz-SignedHeaders=host&x-amz-checksum-mode=ENABLED&x-id=GetObject)
