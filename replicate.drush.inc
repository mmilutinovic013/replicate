<?php
/**
 * Implements hook_drush_command().
 */
function replicate_drush_command() {

  $items['replicate'] = array(
    'description' => 'Replicate an Enitity via Drush!',
    'arguments' => array(
      'entity-type' => dt('Type of Entity (eg. Node) that you wish to replicate'),
    ),
    'arguments' => array(
      'id-number' => dt('ID value of the specified Entity Type (eg. NodeID'),
    ),
    'aliases' => array('rep'),
    'examples' => array(
      'drush replicate node 1' =>
        'Node 1 is replicated via drush using full command',
      'drush rep node 1' =>
        'Node 1 is replicated via drush using aliased command',
    ),
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