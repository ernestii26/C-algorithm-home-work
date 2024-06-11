import shlex, subprocess
# command_line = input()
# args = shlex.split(command_line)
# print(args)
#"""
args = ['gcc', 'correct.c', '-o', 'main1']
subprocess.run(args)
args = ['gcc', 'test2.c', '-o', 'main2']
subprocess.run(args)
while(True):
    args = ['python3', '../debug/generator.py']
    subprocess.run(args, stdout=open('input2.txt', 'w'))

    subprocess.run(['./main1'], stdin=open("input2.txt", "r"), stdout=open("output1", "w"))
    subprocess.run(['./main2'], stdin=open("input2.txt", "r"), stdout=open("output2", "w"))
    p = subprocess.run(['diff','-w', './output1', './output2'], capture_output=True)
    if p.stdout != b'':
        break
#"""
end = 1