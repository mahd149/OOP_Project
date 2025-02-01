import csv
import random
import os

# List of Bangladeshi districts and their corresponding zip codes
bangladesh_districts_zip = {
    "Dhaka": "1200",
    "Chittagong": "4000",
    "Khulna": "9000",
    "Rajshahi": "6000",
    "Barisal": "8200",
    "Sylhet": "3100",
    "Rangpur": "5400",
    "Mymensingh": "2200",
    "Comilla": "3500",
    "Narayanganj": "1400",
    "Gazipur": "1700",
    "Jessore": "7400",
    "Bogra": "5800",
    "Dinajpur": "5200",
    "Pabna": "6600",
    "Noakhali": "3800",
    "Faridpur": "7800",
    "Tangail": "1900",
    "Kushtia": "7000",
    "Feni": "3900",
}

# List of blood groups
blood_groups = ["A+", "A-", "B+", "B-", "O+", "O-", "AB+", "AB-"]

# Function to generate random phone numbers
def generate_phone_number():
    return f"01{random.randint(10000000, 99999999)}"

# Generate random donor data
def generate_donor_data(num_entries):
    donors = []
    for _ in range(num_entries):
        name = f"Donor_{random.randint(1, 1000)}"
        blood_group = random.choice(blood_groups)
        age = random.randint(18, 65)
        district = random.choice(list(bangladesh_districts_zip.keys()))
        zip_code = bangladesh_districts_zip[district]
        contact = generate_phone_number()
        donors.append([name, blood_group, age, zip_code, contact])
    return donors

# Write data to CSV file in the current directory
def write_to_csv(filename, data):
    # Get the current directory
    current_directory = os.getcwd()
    file_path = os.path.join(current_directory, filename)
    
    with open(file_path, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Name", "Blood Group", "Age", "Zip", "Contact"])  # Header
        writer.writerows(data)

# Generate 100 donor entries
donor_data = generate_donor_data(100)

# Write to CSV file in the current directory
write_to_csv("donor_info.csv", donor_data)

print(f"CSV file 'donor_info.csv' has been created in the current directory: {os.getcwd()}")