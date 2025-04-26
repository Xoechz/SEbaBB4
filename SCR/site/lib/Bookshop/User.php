<?php

namespace Bookshop;

/**
 * User
 *
 *
 * @extends Entity
 * @package
 * @subpackage
 * @author     John Doe <jd@fbi.gov>
 */
class User extends Entity {

    private string $userName;
    private string $passwordHash;

    public function __construct(int $id, string $userName, string $passwordHash) {
        parent::__construct($id);
        $this->userName = $userName;
        $this->passwordHash = $passwordHash;
    }

    /**
     * getter for the private parameter $userName
     *
     * @return string
     */
    public function getUserName() : string {
        return $this->userName;
    }

    /**
     * getter for the private parameter $passwordHash
     *
     * @return string
     */
    public function getPasswordHash() : string {
        return $this->passwordHash;
    }

}
