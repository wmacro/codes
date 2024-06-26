import json
from pyparsing import nestedExpr

def extract_json_objects(string):
    # 查找所有嵌套的括号对
    nested = nestedExpr('{', '}').searchString(string)
    
    json_objects = []
    for item in nested:
        try:
            # 将提取到的内容转换成 JSON 字符串
            json_str = ''.join(item[0])
            # 尝试解析 JSON 字符串
            json_objects.append(json.loads(json_str))
        except json.JSONDecodeError:
            # 忽略无效的 JSON 对象
            continue
    
    return json_objects

# 示例字符串
example_string = '''
{
    "name": "Alice",
    "age": 30
},
{
    "name": "Bob",
    "age": 25
}
Some other text {
    "name": "Charlie",
    "age": 35
}
'''

# 提取 JSON 对象
json_objects = extract_json_objects(example_string)
for i, obj in enumerate(json_objects):
    print(f"JSON 对象 {i+1}: {obj}")
