import subprocess

# 编译C代码
subprocess.run(["gcc", "-o", "ex17", "ex17.c"])

# 运行测试命令
commands = [
    "./ex17 db.dat c",
    "./ex17 db.dat s 1 John john@example.com",
    "./ex17 db.dat s 2 Alice alice@example.com",
    "./ex17 db.dat l",
    "./ex17 db.dat g 1",
#    "./ex17 db.dat d 1",
    "./ex17 db.dat l"
]

for command in commands:
    subprocess.run(command.split())

# 清理
subprocess.run(["rm", "ex17"])
subprocess.run(["rm", "db.dat"])
