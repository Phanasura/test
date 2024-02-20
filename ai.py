
import openai
openai.api_key = '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'
#openai.api_key = "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"
def inp(text="Enter"):
    print(text+" >>>   ('ok' = stop)")
    content_lines = []
    while True:
        line = input()
        if line.lower().strip() == "send":
            break
        content_lines.append(line)
    content = "\n".join(content_lines)
    return content.strip()

def mainai():
    messages = []
    system_msg = inp("What type of chatbot would you like to create?")
    messages.append({"role": "system", "content": system_msg})
    try:
        print("Your new assistant is ready!")
        while True:
            message = inp("Enter your message")
            if not message:
                continue
            elif message.lower() == 'q':
                break
            messages.append({"role": "user", "content": message})
            response = openai.ChatCompletion.create(
                model="gpt-3.5-turbo",
                messages=messages)
            reply = response["choices"][0]["message"]["content"]
            messages.append({"role": "assistant", "content": reply})
            print("\n" + reply + "\n")
    except Exception:
        print("Expire ID")
        new_api = inp("Enter new api key")
        openai.api_key = new_api
        mainai()


mainai()



'''
def checkapi():
    wapi = False
    try:
        response = openai.ChatCompletion.create(model="gpt-3.5-turbo", messages=[{"role": "user", "content": "hello"}])
        if response:
            print(
                "API_KEY VALID >>> CHATBOT INITIALIZING\n")
            return
    except Exception:
        wapi = True
    while wapi:
        try:
            print("API_KEY INVALID! \n")
            napi = inp("ENTER NEW API KEY ('q' = quit)")
            if napi.lower() == 'q':
                break
            openai.api_key = napi
            response = openai.ChatCompletion.create(model="gpt-3.5-turbo",
                                                    messages=[{"role": "user", "content": "hello"}])
            if response:
                return
        except Exception:
            pass
def inp(text):
    print(text+">>>")
    content_lines = []
    while True:
        line = input()
        if line.lower().strip() == "send":
            break
        content_lines.append(line)
    content = "\n".join(content_lines)
    return content
import openai
openai.api_key = "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" =>main trisphankhoahoc

completion = openai.ChatCompletion.create(model="gpt-3.5-turbo", messages=[{"role": "user", "content": "Write dfs code c++ and python"}])
print(completion.choices[0].message.content)
'''