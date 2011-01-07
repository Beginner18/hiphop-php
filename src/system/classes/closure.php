<?php

/**
 * Internal class. Should NOT use directly at all.
 */
class Closure {
  protected $func = '';
  protected $vars = array();

  public function __construct($func, $vars) {
    $this->func = $func;
    $this->vars = $vars;
  }

  public function __toString() {
    return $this->func . ':' . hphp_object_pointer($this);
  }

  public function getVars() {
    return $this->vars;
  }
  public function setVars($vars) {
    unset($vars["__cont__"]);
    $this->vars = $vars;
  }
}

/**
 * Internal class. Should NOT use directly at all.
 */
class Continuation extends Closure implements Iterator {
  private $obj;
  public $label = 0;
  private $done = false;
  private $index = -1;
  private $value;
  private $running = false;

  public function __construct($func, $vars, $obj = null) {
    parent::__construct($func, $vars);
    $this->obj = $obj;
  }
  public function update($label, $value, $vars) {
    $this->label = $label;
    $this->value = $value;
    parent::setVars($vars);
  }
  public function done() {
    $this->done = true;
  }

  public function current() {
    if ($this->index < 0) {
      throw new Exception('Need to call next() first');
    }
    return $this->value;
  }
  public function key() {
    if ($this->index < 0) {
      throw new Exception('Need to call next() first');
    }
    return $this->index;
  }
  public function next() {
    if ($this->done) {
      throw new Exception('Continuation is already finished');
    }
    if ($this->running) {
      throw new Exception('Continuation is already running');
    }
    $this->running = true;

    ++$this->index;
    try {
      if ($this->obj) {
        $tokens = explode('::', $this->func);
        $func = $tokens[1];
        $this->obj->$func($this);
      } else {
        call_user_func($this->func, $this);
      }
    } catch (Exception $e) {
      $this->running = false;
      $this->done = true;
      throw $e;
    }

    $this->running = false;
  }
  public function rewind() {
    throw new Exception('Cannot rewind on a Continuation object');
  }
  public function valid() {
    return !$this->done;
  }
}
