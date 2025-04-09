import subprocess
import base64
import random
import string
import os

def generate_random_data(length):
    return bytes([random.randint(0, 255) for _ in range(length)])

def test_ascii85():
    for _ in range(10):
        data = generate_random_data(random.randint(1, 100))
        encoded = subprocess.run(['./ascii85'], input=data, capture_output=True, check=True).stdout
        decoded = subprocess.run(['./ascii85', '-d'], input=encoded, capture_output=True, check=True).stdout
        assert decoded == data, f"Round trip failed for data: {data}"
    
    invalid_data = b"invalid!@#"
    result = subprocess.run(['./ascii85', '-d'], input=invalid_data, capture_output=True)
    assert result.returncode != 0, "Decoder should fail on invalid input"
    
    print("All integration tests passed!")

if __name__ == "__main__":
    test_ascii85()