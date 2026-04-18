# 🚀 Laboratory Practice V (LP-V)

## High Performance Computing (HPC) & Deep Learning 

---

## 📌 Overview

This repository contains all practical assignments completed as part of **Laboratory Practice V (410255)** under SPPU.

The work is divided into:

* 🖥️ **High Performance Computing (HPC) using C++**
* 🤖 **Deep Learning Assignments**
* 📊 **Mini Projects**

---

## 🧠 Course Outcomes Covered

* Performance analysis of sequential vs parallel algorithms
* Implementation of parallel algorithms using OpenMP & CUDA
* Application of Deep Learning models for regression & classification
* Understanding CNN and Neural Networks

---

## 📂 Repository Structure

```
LP-V/
│── HPC/
│   ├── BFS_OpenMP.cpp
│   ├── DFS_OpenMP.cpp
│   ├── Parallel_Bubble_Sort.cpp
│   ├── Parallel_Merge_Sort.cpp
│   ├── Reduction_Operations.cpp
│   ├── CUDA_Vector_Addition.cu
│   ├── CUDA_Matrix_Multiplication.cu
│
│── DeepLearning/
│   ├── Assignment_1/
│   ├── Assignment_2A/   (From Sir's Blog)
│   ├── Assignment_2B/   (From Sir's Blog)
│   ├── Assignment_3B/   (From Sir's Blog)
│
│── Mini_Project/HPC -db.cpp/DL-Gender_and_Age_Detection_using_CNN.ipynb
│── datasets/
│── README.md
```

---

# 🖥️ High Performance Computing (HPC) Practicals

## 🔹 Implemented Programs

1. Parallel Breadth First Search (BFS) using OpenMP
2. Parallel Depth First Search (DFS) using OpenMP
3. Parallel Bubble Sort
4. Parallel Merge Sort
5. Parallel Reduction (Min, Max, Sum, Average)
6. CUDA Vector Addition
7. CUDA Matrix Multiplication

---

## ▶️ How to Run HPC Programs

### 🔸 Compile (OpenMP)

```bash
g++ filename.cpp -fopenmp -o output
```

### 🔸 Run

```bash
./output
```

---

### 🔸 Compile (CUDA)

```bash
nvcc filename.cu -o output
```

### 🔸 Run

```bash
./output
```

---

# 🤖 Deep Learning Assignments

## ⚠️ Important Note

Assignments **2A, 2B, and 3B** are implemented using:

* Code directly referenced from **faculty (sir's) blog**
* Standard datasets (Boston Housing, MNIST Fashion, IMDB, etc.)

These are used strictly for **academic learning purposes**.

---

## 📌 Assignment Details

### 🔹 Assignment 1

* Linear Regression using Deep Neural Network
* Dataset: Boston Housing

---

### 🔹 Assignment 2A (From Sir’s Blog)

* Multiclass Classification using Deep Neural Network
* Dataset: OCR Letter Recognition

---

### 🔹 Assignment 2B (From Sir’s Blog)

* Binary Classification using Deep Neural Network
* Dataset: IMDB Movie Reviews

---

### 🔹 Assignment 3B (From Sir’s Blog)

* CNN Model for Image Classification
* Dataset: MNIST Fashion Dataset

---

## ▶️ How to Run Deep Learning Code

### Step 1: Install Dependencies

```bash
pip install numpy pandas matplotlib tensorflow keras
```

---

### Step 2: Run Program

```bash
python filename.py
```

---

### Step 3: Dataset Setup

* Download datasets from:

  * UCI Repository (OCR dataset)
  * Keras datasets (IMDB, MNIST)
* Place them inside `/datasets` folder

---

# 📊 Mini Projects

## 🔹 HPC Mini Project

* Focus on performance optimization using parallel computing

## 🔹 Deep Learning Mini Project

* Real-world prediction/classification problem using Neural Networks

---

# 📈 Performance Analysis

All HPC programs include:

* Sequential execution
* Parallel execution
* Time comparison

---

# ⚠️ Important Guidelines

❌ Do NOT upload:

* Large datasets
* `.env` files
* System-generated files

✅ Include:

* Source code
* Sample input/output
* Documentation

---

# 🎯 Learning Outcomes

* Hands-on experience with OpenMP & CUDA
* Understanding parallel vs sequential performance
* Practical knowledge of Deep Learning models
* Implementation of CNN & classification models

---

# ❗ Disclaimer

Some Deep Learning assignments (2A, 2B, 3B) are implemented using reference material from faculty resources.
This repository is intended for **educational and academic use only**.

---

# 🙌 Author

**Tejas Gaikwad**

---

# ⭐ Support

If you find this helpful, give it a ⭐ on GitHub!
