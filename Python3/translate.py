import json
import requests

def translation(word):
    """
    翻译函数
    :param word:
    :return:
    """
    # 有道词典 api
    url = 'http://fanyi.youdao.com/translate?smartresult=dict&smartresult=rule&smartresult=ugc&sessionFrom=null'
    # word 为需要翻译的词或者句子
    data = {
        'i':word,
        'from':'AUTO',
        'to':'Auto',
        'doctype':'json',
        'version':'2.1',
        'keyfrom':'fanyi.web',
        'action':'FY_BY_CLICKBUTTION',
        'typoResult':'false'
    }
    response = requests.post(url,data=data)
    if response.status_code == 200:
        return response.text
    else:
        print("出错了，请再试一次")
        return None

def get_result(response):
    result = json.loads(response)
    print(result)
    print("输入的词/句为：%s" % result['translateResult'][0][0]['src'])
    print("翻译的词/句为：%s" % result['translateResult'][0][0]['tgt'])

def main():
    word = input("请输入需要翻译的词或句子:")
    translate = translation(word)
    get_result(translate)

if __name__ == "__main__":
    main()
