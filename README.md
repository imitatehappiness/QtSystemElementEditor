# QtSystemElementEditor

>**PostgreSQL:**  9.6 32bit
>
>**Compiler:**  MinGW 5.3.0 32bit
>
>**Profile Qt:**  5.11.0 MinGW 32bit

The program is designed for editing table elements.

The root elements are entries with type=1. Only elements of type=1 can be nested in each other. They have nested elements of type 2 and/or 3.

Data from the database is displayed in the ***"System Composition"*** window.

The "Type 1" elements are displayed in bold. For them, the do not
show type value.Depending on the numeric value of type, show the corresponding text: ***"Type 2" / "Type 3".***

Only when an element of type "Type 1" is selected in the tree in the right tables
show only its directly nested elements, if any, with "Type 2" elements in the upper table, and "Type 3" elements in the lower table.

In the "System Composition" three, you can edit the ***"Type"*** column using ***QComboBox***. Write the changed values to the database. In the right tables ***("Elements Type n")***, only the ***"Size"*** column is available for editing. Write the changed values to the database. When displaying the size value, show all negative values in ***bold red***.

<p align="center">
  <img src="https://user-images.githubusercontent.com/79199956/217393420-f556f576-9836-4bd3-91d4-7a570d95a73a.png" />
</p>
