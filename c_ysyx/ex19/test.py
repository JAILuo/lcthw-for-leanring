import subprocess

# Compile the game
subprocess.run(["make"])

# Test moving in different directions
print("Testing moving in different directions:")
subprocess.run(["./ex19"], input="n\n", text=True)
subprocess.run(["./ex19"], input="s\n", text=True)
subprocess.run(["./ex19"], input="e\n", text=True)
subprocess.run(["./ex19"], input="w\n", text=True)

# Test attacking
print("Testing attacking:")
subprocess.run(["./ex19"], input="a\n", text=True)

# Test listing available directions
print("Testing listing available directions:")
subprocess.run(["./ex19"], input="l\n", text=True)

# Clean up
subprocess.run(["make", "clean"])
