
<?php

use Bookshop\Book;
use Data\DataManager;

$categories = DataManager::getCategories();
$categoryId = isset($_REQUEST['categoryId']) ? (int) $_REQUEST['categoryId'] : 0;
$books = $categoryId > 0 ? DataManager::getBooksByCategory($categoryId) : null;


require_once "views/partials/header.php";
?>



<div class="page-header">
    <h2>List of categories</h2>
</div>

<ul class="nav nav-tabs">
    <?php foreach($categories as $category) { ?>
        <li role="presentation" class="navitem">
            <button class="nav-link
                <?php if($category->getId() == $categoryId){ ?>active<?php } ?>">
                <a href="<?php echo $_SERVER['PHP_SELF']; ?>?view=list&categoryId=<?php echo $category->getId(); ?>"><?php echo $category->getName(); ?></a>
            </button>

        </li>
    <?php } // end foreach ?>

</ul>




<?php
var_dump($books);

require_once "views/partials/footer.php";
?>
