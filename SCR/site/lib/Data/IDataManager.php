<?php

namespace Data;
interface IDataManager {

    public static function getCategories() : array;
    public static function getBooksByCategory(int $categoryId) : array;

}