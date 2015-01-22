<?php
/**
 * Implements hook_drush_command().
 */
function replicate_drush_command() {

  $items['replicate'] = array(
    'description' => 'Demonstrate how Drush commands work.',
    'aliases' => array('rep'),
  );

  return $items;
}
function demo_drush_print_statement() {
  drupal_set_message(t('Hello world!'));
}
/**
 * Callback for the drush-demo-command command
 */
function drush_drush_demo_command() {
  demo_drush_print_statement();
}