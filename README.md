
<p align="center">
  <a href="https://github.com/imitatehappiness/QtSystemElementEditor">
      <img width="128" alt="multiple-users-silhouette" src="https://cdn-icons-png.flaticon.com/512/9693/9693552.png">
  </a>
  <h3 align="center"></h3>
</p>

# System Elements Editor

The "Table Elements Editor" program is designed for editing table elements in a hierarchical manner. The root elements are entries with type=1. Only elements of type=1 can be nested within each other. These root elements may contain nested elements of type=2 and/or type=3.

The program retrieves data from a database and displays it in the "System Composition" window. The elements of type=1 are displayed in bold, and their type value is not shown. Instead, the corresponding text "Type 2" or "Type 3" is displayed based on their numeric type value.

## System Composition Window

+ The "System Composition" window displays a hierarchical tree of elements retrieved from the database.
+ Elements of type=1 are shown in bold, and their type value is hidden, displaying "Type 2" or "Type 3" based on the numeric value.
+ When you select an element of type=1 in the tree, the right tables display its directly nested elements (if any).
+ In the upper table, "Elements Type 2" are shown, and in the lower table, "Elements Type 3" are displayed.

## Editing Elements

+ In the "System Composition" tree view, you can edit the "Type" column using a QComboBox. Any changes made to the type value will be updated and saved to the database.
+ In the right tables ("Elements Type 2" and "Elements Type 3"), you can edit the "Size" column. The program will write the changes back to the database.
+ When displaying the "Size" value, all negative values are shown in bold red for better visibility.

>**PostgreSQL:**  9.6 32bit
>
>**Compiler:**  MinGW 5.3.0 32bit
>
>**Profile Qt:**  5.11.0 MinGW 32bit

## Example

<div align="center">
  <video src="https://user-images.githubusercontent.com/79199956/223730727-e9d0a29d-b12b-4723-8be4-38124e3faf8d.mp4"/>
<div/>





